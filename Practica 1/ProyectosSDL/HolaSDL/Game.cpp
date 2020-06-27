#include "Game.h"
#include <time.h>

Game::Game()
{
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("Practica 1: Bow and Arrow", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	if (window_ == nullptr || renderer_ == nullptr) {
		throw "SDL ERROR \n";
	}

	initGame();
}

Game::~Game()
{
	closeGame();
}

void Game::render() const
{
	if (bow_ != nullptr) {
		bow_->render();
	}
	for (auto& arrow : arrows_) {
		arrow->render();
	}

	for (auto& balloon : balloons_) {
		balloon->render();
	}
}

void Game::update()
{

	if (bow_ != nullptr) {
		bow_->update();
	}
	for (auto& arrow : arrows_) {
		arrow->update();
	}

	for (auto& balloon : balloons_) {
		balloon->update();
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;
		else {
			bow_->handleEvents();
		}
	}
}

void Game::run()
{
	while (!SDL_QuitRequested() && !exit) {
		update();
		handleEvents();
		render();
	}
}

void Game::shoot(Arrow* arrow)
{
	arrows_.push_back(arrow);
}

void Game::initGame()
{
	
}

void Game::closeGame()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}
