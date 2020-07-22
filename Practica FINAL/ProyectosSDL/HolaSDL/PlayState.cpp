#include "PlayState.h"
#include "SDLApp.h"
#include "MenuButton.h"
PlayState::~PlayState()
{
}

void PlayState::init()
{
	// add scoreboard

	//add bow

	//add n butterflies


	
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
	createBalloon();
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

void PlayState::killGameObject(GameObject* go)
{

}

void PlayState::shoot(Arrow* arrow)
{
}

bool PlayState::collision(Balloon* balloon)
{
	return false;
}

void PlayState::createButterflies(int n)
{
}

void PlayState::createBalloon()
{
	if (rand() % 15==0) {

	}
}
