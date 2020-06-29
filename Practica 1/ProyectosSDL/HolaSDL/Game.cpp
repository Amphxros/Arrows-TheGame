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
	SDL_Rect dest;
	dest.x = dest.y = 0;
	dest.w = WIN_WIDTH;
	dest.h = WIN_HEIGHT;

	textures_[BG]->render(dest);

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
		if (event.type == SDL_QUIT) {
			exit = true;
		}
		else {
			bow_->handleEvents(event);
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
	closeGame();
}

void Game::shoot(Arrow* arrow)
{
	arrows_.push_back(arrow);
}

bool Game::collision(Balloon* b, int rows, int cols)
{
	SDL_Rect dest = b->getCollisionDest();
	bool col = false;

	int i = 0;
	while (!col && i < arrows_.size()) {
		SDL_Rect arrow_dest = arrows_[i]->getPointRect();

		if (SDL_HasIntersection(&dest, &arrow_dest)) {
			col = true;
		}
		++i;
	}

	return col;
}

void Game::initGame()
{
	bow_ = new Bow({ 0,0 }, { 0, 4}, 100, 150, textures_[BOW_A], textures_[BOW_B], textures_[ARROW], this);

	for (int i = 0; i < NUM_TEXTURES; i++) {
		textures_[i] = new Texture(renderer_, routesTextures[i].route, routesTextures[i].rows, routesTextures[i].columns);
	}
}

void Game::closeGame()
{
	delete bow_;
	bow_ = nullptr;
	
	for (auto& arrow : arrows_) {
		delete arrow;
		arrow = nullptr;
	}
	
	for (auto& balloon : balloons_) {
		delete balloon;
		balloon = nullptr;
	}
	
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::createBallons()
{
	if (rand() % 20 == 1) {
		Balloon* balloon = new Balloon({ (double)((double)WIN_WIDTH / 2) + rand() % (WIN_WIDTH / 2),(double)WIN_HEIGHT }, { -1,2 + (double)(rand() % 4) }, 3072/6, 3584/7, textures_[BALLOON], this);
		balloons_.push_back(balloon);
	}
}
