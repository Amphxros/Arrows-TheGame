#include "PauseState.h"
#include "SDLApp.h"
#include "MenuButton.h"

PauseState::~PauseState()
{
}

void PauseState::init()
{
	MenuButton* button = new MenuButton({ app_->getWidth() / 4 , app_->getHeight() /4 }, app_->getWidth() / 2, app_->getHeight() / 4, app_->getTexture(TextureOrder::BUTTON), this, SDLApp::resumeApp);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton({ app_->getWidth() / 4 , app_->getHeight() /2 }, app_->getWidth() / 2, app_->getHeight() / 4, app_->getTexture(TextureOrder::BUTTON), this, SDLApp::toMenu);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton({ app_->getWidth() / 4 , 3* app_->getHeight() /4 }, app_->getWidth() / 2, app_->getHeight() / 4, app_->getTexture(TextureOrder::BUTTON), this, SDLApp::savePlayState);
	addEventHandler(button);
	addGameObject(button);
}

void PauseState::render() const
{
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = app_->getWidth();
	dest.h = app_->getHeight();
	app_->getTexture(TextureOrder::BACKGROUND2)->render(dest);
	GameState::render();
}

void PauseState::update()
{
	GameState::update();
}

void PauseState::handleEvents(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			app_->resumeApp(app_);
		}
	}
	GameState::handleEvents(event);
}
