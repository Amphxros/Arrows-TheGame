#include "PlayState.h"
#include "SDLApp.h"
#include "MenuButton.h"
PlayState::~PlayState()
{
}

void PlayState::init()
{
	MenuButton* button = new MenuButton({ WIN_WIDTH / 4 , 0 }, WIN_WIDTH / 2, WIN_HEIGHT / 4, app_->getTexture(TextureOrder::BUTTON), this, SDLApp::toPause);
	addEventHandler(button);
	addGameObject(button);


}

void PlayState::render() const
{
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = WIN_WIDTH;
	dest.h = WIN_HEIGHT;
	app_->getTexture(TextureOrder::BACKGROUND2)->render(dest);
	GameState::render();
}

void PlayState::update()
{
	GameState::update();
}

void PlayState::handleEvents(SDL_Event& event)
{
	if (event.type==SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			app_->toPause(app_);
		}
	}
	GameState::handleEvents(event);
}

void PlayState::createButterflies(int n)
{
}

void PlayState::createBalloons()
{
}
