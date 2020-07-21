#pragma once
#include <SDL.h>
#include "GameStateMachine.h"

using namespace std;

using uint = unsigned int;

class SDLApp
{
public:
	SDLApp();
	~SDLApp();

	void run();
	void render() const;
	void update();
	void handleEvents();

	// Metodos estaticos para los callbacks
	static void quitApp(SDLApp* app);
	static void resumeApp(SDLApp* app);
	static void loadPlayState(SDLApp* app);
	static void savePlayState(SDLApp* app);
	static void toPlay(SDLApp* app);
	static void toPause(SDLApp* app);
	static void toMenu(SDLApp* app);
	static void toEnd(SDLApp* app);

private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	static GameStateMachine* stateMachine_;

	static bool exit_;

};

