#pragma once

#include "Texture.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include "Balloon.h"
#include "Arrow.h"
#include "Bow.h"


using uint = unsigned int;
const int NUM_TEXTURES = 5;



enum TextureID { BG, BOW_A, BOW_B, ARROW, BALLOON };
struct Routes {
	std::string route;
	int rows, columns;
};



class Game
{
public:
	Game();
	~Game();

	void render() const;
	void update();
	void handleEvents();

	void run();
	void shoot(Arrow* arrow);

	bool collision(Balloon* b, int rows, int cols);
	inline uint getWindowWidth() { return WIN_WIDTH; }
	inline uint getWindowHeight() { return WIN_HEIGHT; }


private:
	const uint WIN_WIDTH = 800;
	const uint WIN_HEIGHT = 800;
	const int FRAMERATE = 60;
	
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	
	Bow* bow_;
	std::vector<Arrow*> arrows_;
	std::vector<Balloon*> balloons_;
	Texture* textures_[NUM_TEXTURES];

	bool exit = false;


	void initGame();
	void closeGame();
	void createBallons();

	Routes routesTextures[NUM_TEXTURES] = {
	{"..\\images\\bg1.png", 1, 1},
	{ "..\\images\\Bow1.png",1,1 },
	{ "..\\images\\Bow2.png",1,1 },
	{ "..\\images\\Arrow1.png",1,1 },
	{ "..\\images\\balloons.png",7,6 }
	};
};

