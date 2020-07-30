#include "SDLApp.h"
#include <time.h>
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"

GameStateMachine* SDLApp::stateMachine_ = nullptr;
bool SDLApp::exit_ = false;
SDLApp::SDLApp()
{
	srand(time(NULL));
	int e= SDL_Init(SDL_INIT_EVERYTHING);
	if (e > 0) {
		//EXCEPTION
	}

	window_ = SDL_CreateWindow("BOW and ARROW", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	
	if (!renderer_ || !window_) {
		//EXCEPTION
	}
	loadTextures();
	stateMachine_ = new GameStateMachine();
	stateMachine_->pushState(new MainMenuState(this));
}

SDLApp::~SDLApp()
{
	delete stateMachine_;
	stateMachine_ = nullptr;
	

	
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void SDLApp::run()
{
	while (!exit_ || stateMachine_ != nullptr) {
		render();
		update();
		handleEvents();
	}
}

void SDLApp::render() const
{
	SDL_RenderClear(renderer_);
	stateMachine_->getCurrentState()->render();
	SDL_RenderPresent(renderer_);
}

void SDLApp::update()
{

	stateMachine_->getCurrentState()->update();
}

void SDLApp::handleEvents()
{
	SDL_Event ev;

	while (SDL_PollEvent(&ev) && !exit_)
	{
		stateMachine_->getCurrentState()->handleEvents(ev);
		if (ev.type == SDL_QUIT)
		{
			exit_ = true;
		}
	}
}

void SDLApp::quitApp(SDLApp* app)
{
	exit_ = true;
}

void SDLApp::resumeApp(SDLApp* app)
{
	stateMachine_->popState();
}

void SDLApp::loadPlayState(SDLApp* app)
{
	int code = -1;
	while (code < 0) {
		cout << "Introduce tu codigo: " << endl;
		cin >> code;
	}
	stateMachine_->pushState(new PlayState(app));
	static_cast<PlayState*>(stateMachine_->getCurrentState())->loadFromFile(code);
}

void SDLApp::savePlayState(SDLApp* app)
{
	stateMachine_->popState();
	int code = -1;
	while (code < 0) {
		cout << "Introduce tu codigo: " << endl;
		cin >> code;
	}
	static_cast<PlayState*>(stateMachine_->getCurrentState())->saveToFile(code);
}

void SDLApp::toPlay(SDLApp* app)
{
	stateMachine_->pushState(new PlayState(app));
}

void SDLApp::toPause(SDLApp* app)
{
	stateMachine_->pushState(new PauseState(app));

}

void SDLApp::toMenu(SDLApp* app)
{
	while (stateMachine_->getCurrentState()->getState()!=State::MENU)
	{
		stateMachine_->popState();
	}
	cout << "to menu" << endl;
}

void SDLApp::toEnd(SDLApp* app)
{

	cout << "to end" << endl;
}

void SDLApp::loadTextures()
{
	textures_.emplace(BACKGROUND1, new Texture(renderer_, "..\\images\\bg1.png", 1, 1));
	textures_.emplace(BACKGROUND2, new Texture(renderer_, "..\\images\\bg_spring_trees_1.png", 1, 1));
	textures_.emplace(BACKGROUND3, new Texture(renderer_, "..\\images\\Cartoon_Forest_BG_01.png", 1, 1));
	textures_.emplace(BACKGROUND4, new Texture(renderer_, "..\\images\\Cartoon_Forest_BG_02.png", 1, 1));
	textures_.emplace(BOW_1, new Texture(renderer_, "..\\images\\Bow1.png", 1, 1));
	textures_.emplace(BOW_2, new Texture(renderer_, "..\\images\\Bow2.png", 1, 1));
	textures_.emplace(BALLOONS, new Texture(renderer_, "..\\images\\balloons.png", 7, 6));
	textures_.emplace(ARROW_1, new Texture(renderer_, "..\\images\\Arrow1.png", 1, 1));
	textures_.emplace(ARROW_2, new Texture(renderer_, "..\\images\\Arrow2.png", 1, 1));
	textures_.emplace(BUTTERFLY, new Texture(renderer_, "..\\images\\butterfly2.png", 4, 10));
	textures_.emplace(REWARDS, new Texture(renderer_, "..\\images\\rewards.png", 10,8));
	textures_.emplace(SCOREBOARD, new Texture(renderer_, "..\\images\\digits1.png", 1, 10));
	textures_.emplace(BUBBLE, new Texture(renderer_, "..\\images\\bubble.png", 1, 1));
	textures_.emplace(BUTTON, new Texture(renderer_, "..\\images\\button.png", 1, 1));
	textures_.emplace(BUTTON_START, new Texture(renderer_, "..\\images\\button.png", 1, 1));
	textures_.emplace(BUTTON_LOAD, new Texture(renderer_, "..\\images\\button.png", 1, 1));
	textures_.emplace(BUTTON_QUIT, new Texture(renderer_, "..\\images\\button.png", 1, 1));
	textures_.emplace(BUTTON_RESUME, new Texture(renderer_, "..\\images\\button.png", 1, 1));

}
