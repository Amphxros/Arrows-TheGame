#include "MainMenuState.h"
#include "MenuButton.h"



MainMenuState::MainMenuState(SDLApp* app):
	GameState(app) {
	init();
}

MainMenuState::~MainMenuState()
{
	for (auto& go : gObjects_) {
		delete go;
	}

	gObjects_.clear();
}

void MainMenuState::init()
{

	MenuButton* button = new MenuButton({ WIN_WIDTH / 4, WIN_HEIGHT / 4 }, WIN_WIDTH / 2, WIN_HEIGHT / 4, app_->getTexture(TextureOrder::BUTTON), this, SDLApp::loadPlayState);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton({ WIN_WIDTH / 4 ,WIN_HEIGHT / 2 }, WIN_WIDTH / 2, WIN_HEIGHT / 4, app_->getTexture(TextureOrder::BUTTON), this, SDLApp::toPlay);
	addEventHandler(button);
	addGameObject(button);
	
	button = new MenuButton({ WIN_WIDTH / 4 , 3* WIN_HEIGHT / 4 }, WIN_WIDTH / 2, WIN_HEIGHT / 4, app_->getTexture(TextureOrder::BUTTON), this, SDLApp::quitApp);
	addEventHandler(button);
	addGameObject(button);

}

void MainMenuState::render() const
{
	SDL_Rect dest;
	
	dest.x = 0;
	dest.y = 0;
	dest.w = WIN_WIDTH;
	dest.h = WIN_HEIGHT;

	app_->getTexture(TextureOrder::BACKGROUND1)->render(dest);
	GameState::render();
}

void MainMenuState::update()
{
	GameState::update();
}

void MainMenuState::handleEvents(SDL_Event& event)
{
	GameState::handleEvents(event);
}
