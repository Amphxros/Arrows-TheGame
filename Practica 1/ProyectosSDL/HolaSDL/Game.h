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

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 800;



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

private:
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	bool exit = false;

	Bow* bow_;
	std::vector<Arrow*> arrows_;
	std::vector<Balloon*> balloons_;

	void initGame();
	void closeGame();
};

