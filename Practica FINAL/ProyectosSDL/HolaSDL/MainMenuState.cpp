#include "MainMenuState.h"
#include "MenuButton.h"

MainMenuState::MainMenuState():
	GameState() { }

MainMenuState::MainMenuState(SDLApp* app):
	GameState(app) {
	init();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::init()
{
	MenuButton* button = new MenuButton({ WIN_WIDTH / 4,WIN_HEIGHT / 4 }, WIN_WIDTH / 2, WIN_HEIGHT / 4, app_->getTexture(TextureOrder::BUTTON), this, SDLApp::loadPlayState);
	addEventHandler(button);
	addGameObject(button);

	button = new MenuButton({ WIN_WIDTH / 2 ,WIN_HEIGHT / 4 }, WIN_WIDTH / 2, WIN_HEIGHT / 4, app_->getTexture(TextureOrder::BUTTON), this, SDLApp::toPlay);
	addEventHandler(button);
	addGameObject(button);
	
	button = new MenuButton({ 3* WIN_WIDTH / 4 ,WIN_HEIGHT / 4 }, WIN_WIDTH / 2, WIN_HEIGHT / 4, app_->getTexture(TextureOrder::BUTTON), this, SDLApp::quitApp);
	addEventHandler(button);
	addGameObject(button);

}

void MainMenuState::render() const
{

}

void MainMenuState::update()
{
	GameState::update();
}

void MainMenuState::handleEvents(SDL_Event& event)
{
	GameState::handleEvents(event);
}
