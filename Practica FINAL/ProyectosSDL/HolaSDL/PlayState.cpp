#include "PlayState.h"
#include "SDLApp.h"
#include <math.h>
#include <string>
#include "GameObject.h"

PlayState::~PlayState()
{
	clear();
}

void PlayState::init()
{
	Arrow::count = 0;
	Balloon::count = 0;
	Butterfly::count = 0;
	Reward::count = 0;
	

}

void PlayState::createGame()
{
	background_ = app_->getTexture(TextureOrder::BACKGROUND2);

	// add scoreboard
	score_ = new ScoreBoard(Vector2D(WIN_WIDTH / 2, 0), 20, 20, app_->getTexture(TextureOrder::SCOREBOARD), app_->getTexture(TextureOrder::ARROW_2), this);
	addGameObject(score_);
	score_->setPoints(0);
	score_->setArrows(10);

	//add bow
	bow_ = new Bow(Vector2D(0, 0), Vector2D(0, 5), 100, 150, app_->getTexture(TextureOrder::BOW_1), app_->getTexture(TextureOrder::BOW_2), app_->getTexture(TextureOrder::ARROW_1), this);
	addGameObject(bow_);
	addEventHandler(bow_);

	//add n butterflies
	createButterflies(10);
}

void PlayState::render() const
{
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = WIN_WIDTH;
	dest.h = WIN_HEIGHT;
	background_->render(dest);
	GameState::render();
	score_->render(); //esto es para que se renderice encima del resto de objetos 
}

void PlayState::update()
{
	if (Butterfly::count!= 0 && score_->getArrows()>0) {
		GameState::update();
		createBalloon();
	}
	else {
		if (Butterfly::count == 0) {
			cout << "all butterflies are dead " << endl;
		}
		else {
			cout << "there are no more arrows" << endl;
		}

		app_->quitApp(app_);
	}
}

void PlayState::handleEvents(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			app_->toPause(app_);
		}
	}
	GameState::handleEvents(event);
}

void PlayState::saveToFile(int seed)
{
	std::ofstream file;
	file.open(std::to_string(seed) + ".sav");
	if (file.is_open()) {
		//guardar nivel, puntuacion y flechas
		file << level << " " << score_->getPoints() << " " << score_->getArrows() << endl;

		//arco
		bow_->saveToFile(file);
		file << endl;

		//flechas
		file << Arrow::count << endl;
		for (Arrow* arrow : arrows_) {
			arrow->saveToFile(file);
			file << endl;
		}

		//globos
		file << Balloon::count << endl;

		for (Balloon* b : balloons_) {
			b->saveToFile(file);
			file << endl;
		}

		//mariposas
		file << Butterfly::count << endl;

		for (Butterfly* b : butterflies_) {

			b->saveToFile(file);
			file << endl;
		}
		//premios
		file << Reward::count << endl;

		for (Reward* r : rewards_) {
			r->saveToFile(file);
			file << endl;
		
		}

		file.close();
	}
	else {
		//error
		throw domain_error("archivo invalido");
	}
}

void PlayState::loadFromFile(int seed)
{
	std::ifstream file;
	file.open(std::to_string(seed) + ".sav");

	if (file.is_open()) {

		score_ = new ScoreBoard(Vector2D(WIN_WIDTH / 2, 0), 20, 20, app_->getTexture(TextureOrder::SCOREBOARD), app_->getTexture(TextureOrder::ARROW_2), this);
		addGameObject(score_);

		int score, level_,arrow;

		file >> level_ >> score >> arrow;
		level = level_;
		setBackground(level);

		//carga el arco
		int posx, posy, speedx, speedy;

		file >> posx >> posy >> speedx >> speedy;
		bow_ = new Bow(Vector2D(posx, posy), Vector2D(speedx, speedy), 100, 150, app_->getTexture(TextureOrder::BOW_1), app_->getTexture(TextureOrder::BOW_2), app_->getTexture(TextureOrder::ARROW_1), this);
		addGameObject(bow_);
		addEventHandler(bow_);
		
		//carga las flechas
		int arrows;
		file >> arrows;
		for (int i = 0; i < arrows; i++) {
			Arrow* a= new Arrow(Vector2D(0, 0), Vector2D(0, 0), (double)100, (double)31,app_->getTexture(TextureOrder::ARROW_1), this);
			a->loadFromFile(file);
			shoot(a);
		}
		score_->setPoints(score);
		score_->setArrows(arrow);
		
		//carga los globos
		int ballons;
		file >> ballons;
		for (int i = 0; i < ballons; i++) {
			Balloon* b = new Balloon(Vector2D(0, 0), Vector2D(0, 0), 400, 400, false, app_->getTexture(TextureOrder::BALLOONS), this);
			b->loadFromFile(file);
			addNewBalloon(b);
		}


		//carga las mariposas
		int butterflies;
		file >> butterflies;
		for (int i = 0; i < butterflies; i++) {
		
			Butterfly* b = new Butterfly(Vector2D(120 + rand() % (WIN_WIDTH - 220), rand() % WIN_HEIGHT), Vector2D(0.15, 0.15), 50, 50, app_->getTexture(TextureOrder::BUTTERFLY), this);
			b->loadFromFile(file);
			addNewButterfly(b);
		}

		//carga los premios
		int rewards;
		file >> rewards;
		for (int i = 0; i < rewards; i++) {
			Reward* r = new Reward(Vector2D(0,0), Vector2D(0,0), 40, 40, app_->getTexture(TextureOrder::REWARDS), app_->getTexture(TextureOrder::BUBBLE), this);
			r->loadFromFile(file);
			addNewReward(r);
		}


	}
	else {
		throw domain_error("archivo corrupto");
	}
}

void PlayState::shoot(Arrow* arrow)
{
	if (score_->getArrows() > 0) {
		Arrow::count++;
		score_->setArrows(score_->getArrows() - 1);
		addGameObject(arrow);
		arrows_.push_back(arrow);
	}
}

void PlayState::addNewReward(Reward* reward)
{
	Reward::count++;
	addGameObject(reward);
	addEventHandler(reward);
	rewards_.push_back(reward);
}

void PlayState::addButterfly(int n)
{
	createButterflies(n);
}

void PlayState::addArrows(int n)
{
	score_->setArrows(score_->getArrows() + n);
}

void PlayState::addPoints(int n)
{
	score_->setPoints(score_->getPoints() + n);
}

void PlayState::addNewBalloon(Balloon* b)
{
	addGameObject(b);
	balloons_.push_back(b);
	Balloon::count++;
}

void PlayState::addNewButterfly(Butterfly* b)
{
	addGameObject(b);
	butterflies_.push_back(b);
	Butterfly::count++;
}

void PlayState::deleteGameObject(std::list<GameObject*>::iterator go)
{
	killObject(go);
}

void PlayState::deleteArrow(std::list<GameObject*>::iterator it)
{
	Arrow::count--;
	killObject(it);
}

void PlayState::deleteBalloon(std::list<GameObject*>::iterator it)
{
	Balloon::count--;
	killObject(it);
}

void PlayState::deleteButterfly(std::list<GameObject*>::iterator it)
{
	Butterfly::count--;
	killObject(it);
}

void PlayState::deleteReward(std::list<GameObject*>::iterator it, std::list<EventHandler*>::iterator ev)
{
	Reward::count--;
	killObject(it);
}

bool PlayState::collisionWithBalloon(Balloon* balloon)
{
	bool col = false;
	auto it = arrows_.begin();

	while (it != arrows_.end() && !col) {

		SDL_Rect* dest_A = &(*it)->getCollisionRect();
		col = SDL_HasIntersection(balloon->GetRect(), dest_A);
		if (col) {
			(*it)->setNumHits((*it)->getNumHits() + 1);

			int p = pow((static_cast<Arrow*>(*it))->getNumHits() - 1, 2)* POINTS_PER_BALLON;
			score_->setPoints(score_->getPoints() + p);
		}
		else {
			it++;
		}

	}
	return col;
}

bool PlayState::collisionWithButterfly(Butterfly* butterfly)
{
	bool col = false;
	auto it = arrows_.begin();

	while (it != arrows_.end() && !col) {

		SDL_Rect* dest_A = &(*it)->getCollisionRect();
		col = SDL_HasIntersection(&(butterfly->getCollisionRect()), dest_A);
		if (col) {
			score_->setPoints(score_->getPoints() - 5);

		}
		else {
			it++;
		}

	}
	return col;
}

bool PlayState::collisionWithReward(Reward* reward)
{
	bool col = false;
	auto it = arrows_.begin();

	while (it != arrows_.end() && !col) {

		SDL_Rect* dest_A = &(*it)->getCollisionRect();
		col = SDL_HasIntersection(&(reward->getCollisionRect()), dest_A);
		if (col) {
			//aqui podemos sumar puntos???
		}
		else {
			it++;
		}

	}
	return col;
}

void PlayState::nextLevel()
{
	level++;
	int score = score_->getPoints();

	if (level % 3 == 0) {
		background_ = app_->getTexture(TextureOrder::BACKGROUND2);
	}
	else if (level % 3 == 1) {
		background_ = app_->getTexture(TextureOrder::BACKGROUND3);
	}
	else if (level%3 == 2) {
		background_ = app_->getTexture(TextureOrder::BACKGROUND4);
	}

	score_->setPoints(score);
	score_->setArrows(10);
}

void PlayState::clear()
{
	delete score_;
	score_ = nullptr;

	for (auto it = gObjects_.begin(); it != gObjects_.end(); ++it) {
		killObject(it);
	}
	gObjectsToErase_.clear();

	arrows_.clear();
	balloons_.clear();
	butterflies_.clear();
	rewards_.clear();

}

void PlayState::createButterflies(int n)
{
	for (int i = 0; i < n; i++) {
		Butterfly* b = new Butterfly(Vector2D(120 + rand() % (WIN_WIDTH - 220), rand() % WIN_HEIGHT), Vector2D(0.15, 0.15), 50, 50, app_->getTexture(TextureOrder::BUTTERFLY), this);
		addNewButterfly(b);
	}
}

void PlayState::createBalloon()
{
	if (rand() % 50 == 0) {
		Balloon* b = new Balloon(Vector2D(100 + rand() % (WIN_WIDTH - 150), WIN_HEIGHT), Vector2D(0, 0.5), 400, 400, true, app_->getTexture(TextureOrder::BALLOONS), this);
		addNewBalloon(b);
	}
}

void PlayState::createReward(Reward* reward)
{

}

void PlayState::cleanMemory()
{
	
}

void PlayState::setBackground(int level)
{
	if (level % 3 == 0) {
		background_ = app_->getTexture(TextureOrder::BACKGROUND2);
	}
	else if (level % 3 == 1) {
		background_ = app_->getTexture(TextureOrder::BACKGROUND3);
	}
	else if (level % 3 == 2) {
		background_ = app_->getTexture(TextureOrder::BACKGROUND4);
	}

}
