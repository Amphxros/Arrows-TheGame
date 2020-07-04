#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Game.h"
#include "Texture.h"
#include <iostream>
#include <time.h>

using namespace std;
using uint = unsigned int;

Game::Game()
{
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);

	window_ = SDL_CreateWindow("BOW and ARROW", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	for (int i = 0; i < N_TEXTURES; i++) {
		textures_[i] = new Texture(renderer_, textures[i].route, textures[i].fil, textures[i].col);
	}

	bow = new Bow({ 0,0 }, { 0, BOW_VELOCITY }, 100, 150, textures_[BT], textures_[BT2], textures_[AT], this);

}

Game::~Game()
{
	closeGame();
}

void Game::run()
{
	while (availableArrows>0) {
		
		handleEvents();
		update();
		render();
		
		SDL_Delay(1000 / FRAME_RATE);

	}

	delete bow;

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		bow->handleEvents(event);
	}
}

void Game::render()
{

	SDL_RenderClear(renderer_);
	textures_[BG]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	bow->render();

	for (auto& arrow : arrows) {
		arrow->render();
	}
	for (auto& balloon : balloons) {
		balloon->render();
	}

	SDL_RenderPresent(renderer_);
}



void Game::update()
{
	bow->update();
	
	for (auto i = 0; i < arrows.size();i++) {
		
		if (!arrows[i]->update()) {
			arrows.erase(arrows.begin()+i);
			//std::cout << arrows.size() << std::endl;
		}
	}
	
	for (auto i = 0; i < balloons.size(); i++) {
	
		if (!balloons[i]->update()) {
			balloons.erase(balloons.begin() + i);
			//std::cout << balloons.size() << std::endl;
		}
	}
	
	balloonGenerate();

}

bool Game::collision(Balloon* balloon_)
{
	for (int i = 0; i < arrows.size(); i++) {
	
		if (SDL_HasIntersection(balloon_->GetRect(), arrows[i]->GetPoint())) {
			return true;
		}
	}
	return false;
}

void Game::shoot(Arrow* arrow)
{
	arrows.push_back(arrow);
	availableArrows--;
}

void Game::balloonGenerate()
{
	if (rand() % 15 == 0) {
		Balloon* b = new Balloon({ (double)(150 + (rand()%(WIN_WIDTH- 200))),(double)WIN_HEIGHT - 100 }, { 0, BALLOON_VELOCITY }, 400, 400, true, textures_[BL], this);
		balloons.push_back(b);
	}
}

void Game::closeGame()
{

	for (auto& arrow : arrows) {
		delete arrow;
	}

	for (auto& balloon : balloons) {
		delete balloon;
	}

	for (auto& tex_ : textures_) {
		delete tex_;
	}
	delete bow;
	
	arrows.clear();
	balloons.clear();
	delete textures_;
	
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}
