#pragma once
#include <SDL.h>
#include "GameStateMachine.h"
#include <map>

using namespace std;

using uint = unsigned int;

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint FRAME_RATE = 50;

const uint POINTS_PER_BALLON = 15;

enum TextureOrder{
	BACKGROUND1,
	BACKGROUND2,
	BACKGROUND3,
	BACKGROUND4,
	BOW_1,
	BOW_2,
	BALLOONS,
	ARROW_1,
	ARROW_2,
	BUTTERFLY,
	REWARDS,
	BUBBLE,
	SCOREBOARD,
	BUTTON,
	BUTTON_START,
	BUTTON_LOAD,
	BUTTON_QUIT,
	BUTTON_RESUME,

	last
};
class SDLApp
{
public:
	SDLApp();
	~SDLApp();

	void run();
	void render() const;
	void update();
	void handleEvents();

	Texture* getTexture(TextureOrder n) { return textures_.at(n); }

	// callbacks

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
	
	std::map<TextureOrder, Texture*> textures_;

	void loadTextures();

};

