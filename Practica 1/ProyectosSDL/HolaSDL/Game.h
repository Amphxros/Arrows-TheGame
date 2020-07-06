#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Texture.h"
#include <iostream>
#include <string>
#include <vector>
#include "Balloon.h"
#include "Arrow.h"
#include "Bow.h"


using namespace std;

using uint = unsigned int;

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint N_TEXTURES = 5;
const uint FRAME_RATE = 50;
const uint BOW_VELOCITY = 5;
const uint BALLOON_VELOCITY = 3;
const uint ARROW_VELOCITY = 4;

enum { BACKGROUND1, BOW_1,BOW_2, BALLOONS, ARROW_1 };

struct Textures
{
	string route;
	int fil;
	int col;
};


class Game
{
public:
	Game::Game();
	Game::~Game();
	
	void run();
	
	void render();
	void update();
	void handleEvents();
	
	bool collision(Balloon* b);
	void shoot(Arrow* arrow);

private:

	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;

	bool exit = false;
	//int points;
	//int arrows;
	Texture* textures_[N_TEXTURES];
	Bow* bow;
	int availableArrows = 10;

	vector<Arrow*> arrows;
	vector<Balloon*> balloons;
	Textures textures [N_TEXTURES] = { 
		{"..\\images\\bg1.png", 1, 1},										
		{"..\\images\\Bow2.png", 1, 1},											
		{"..\\images\\Bow1.png", 1, 1},											
		{"..\\images\\balloons.png", 7, 6},
		{"..\\images\\Arrow1.png", 1, 1} };
	void balloonGenerate();
	void closeGame();

};

