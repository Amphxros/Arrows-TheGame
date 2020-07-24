#include "PlayState.h"
#include "SDLApp.h"
#include "MenuButton.h"
PlayState::~PlayState()
{
}

void PlayState::init()
{
	// add scoreboard
	score_ = new ScoreBoard(Vector2D(WIN_WIDTH/2,0 ), 20, 20, app_->getTexture(TextureOrder::SCOREBOARD), app_->getTexture(TextureOrder::ARROW_2), this);
	addGameObject(score_);
	score_->setPoints(100);
	score_->setArrows(20);
	//add bow
	bow_ = new Bow(Vector2D(0, 0), Vector2D(0, 5), 100, 150, app_->getTexture(TextureOrder::BOW_1), app_->getTexture(TextureOrder::BOW_2), app_->getTexture(TextureOrder::ARROW_1), this);
	addGameObject(bow_);
	addEventHandler(bow_);
	//add n butterflies
	createButterflies(6+rand()%4);

	
}

void PlayState::render() const
{
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = WIN_WIDTH;
	dest.h = WIN_HEIGHT;
	app_->getTexture(TextureOrder::BACKGROUND2)->render(dest);
	GameState::render();
}

void PlayState::update()
{
	if (score_->getArrows() > 0) {
		GameState::update();
		createBalloon();
		cleanMemory();
	}
	else {
		//pasar a otro estado
		cout << "game end" << endl;
	}

}

void PlayState::handleEvents(SDL_Event& event)
{
	if (event.type==SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			app_->toPause(app_);
		}
	}
	GameState::handleEvents(event);
}

void PlayState::killGameObject(GameObject* go)
{
	gObjectsToErase_.emplace_back(go);
}

void PlayState::shoot(Arrow* arrow)
{
	if (score_->getArrows() > 0) {
		gObjects_.push_back(arrow);
		arrows_.push_back(arrow);
		score_->setArrows(score_->getArrows() - 1);
	}
}

bool PlayState::collision(Balloon* balloon)
{
	return false;
}

void PlayState::createButterflies(int n)
{
	for (int i = 0; i < n; i++) {

	}
}

void PlayState::createBalloon()
{
	if (rand() % 15==0) {

	}
}

void PlayState::killArrow(std::list<GameObject*>::iterator it)
{
}

void PlayState::killBalloon(std::list<GameObject*>::iterator it)
{
}

void PlayState::killButterfly(std::list<GameObject*>::iterator it)
{
}

void PlayState::killReward(std::list<GameObject*>::iterator it)
{
}

void PlayState::cleanMemory()
{
	auto it = gObjectsToErase_.begin();

	while (it != gObjectsToErase_.end()) {
		delete(**it);
		gObjects_.erase(*it);
		it++;
	}
	gObjectsToErase_.clear();

}
