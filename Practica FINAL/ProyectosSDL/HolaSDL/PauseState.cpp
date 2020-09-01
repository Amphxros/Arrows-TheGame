#include "PauseState.h"
#include "SDLApp.h"
#include "MenuButton.h"

PauseState::~PauseState()
{
}

void PauseState::init()
{
	MenuButton* button = new MenuButton({ WIN_WIDTH / 4 , WIN_HEIGHT/4 }, WIN_WIDTH / 2, WIN_HEIGHT / 4, app_->getTexture(TextureOrder::BUTTON), this, SDLApp::resumeApp);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton({ WIN_WIDTH / 4 , WIN_HEIGHT/2 }, WIN_WIDTH / 2, WIN_HEIGHT / 4, app_->getTexture(TextureOrder::BUTTON), this, SDLApp::toMenu);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton({ WIN_WIDTH / 4 , 3* WIN_HEIGHT/4 }, WIN_WIDTH / 2, WIN_HEIGHT / 4, app_->getTexture(TextureOrder::BUTTON), this, SDLApp::savePlayState);
	addEventHandler(button);
	addGameObject(button);
}

void PauseState::render() const
{
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = WIN_WIDTH;
	dest.h = WIN_HEIGHT;
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
