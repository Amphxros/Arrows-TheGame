#include "SDLApp.h"
#include <time.h>


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

	stateMachine_ = new GameStateMachine();
	
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
}

void SDLApp::savePlayState(SDLApp* app)
{
}

void SDLApp::toPlay(SDLApp* app)
{

}

void SDLApp::toPause(SDLApp* app)
{
}

void SDLApp::toMenu(SDLApp* app)
{
}

void SDLApp::toEnd(SDLApp* app)
{
}
