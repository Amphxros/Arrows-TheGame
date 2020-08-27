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
			if (b->isNonPunctured()) {
				b->saveToFile(file);
				file << endl;
			}
		}

		//mariposas
		file << Butterfly::count << endl;

		for (Butterfly* b : butterflies_) {

			if (b->isAlive()) {
				b->saveToFile(file);
				file << endl;
			}
		}
		//premios
		file << Reward::count << endl;

		for (Reward* r : rewards_) {
			if (r->getBubbled()) {
				r->saveToFile(file);
			}
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

		int points, arrows;
		file >> level >> points >> arrows;
		score_->setPoints(points);
		score_->setArrows(arrows);

		//carga el arco
		int posx, posy, speedx, speedy;

		file >> posx >> posy >> speedx >> speedy;
		bow_->set(Vector2D(posx, posy), Vector2D(speedx, speedy));

		//carga las flechas
		int count;

		file >> count;

		for (int i = 0; i < count; i++) {
			cout << "cargando flecha" << endl;
			int posx, posy, speedx, speedy;
			file >> posx >> posy >> speedx >> speedy;
			shoot(new Arrow(Vector2D(posx, posy), Vector2D(speedx, speedy), (double)100, (double)31, app_->getTexture(TextureOrder::ARROW_1), this));
		}

		//carga los globos

		file >> count;

		for (int i = 0; i < count; i++) {
			cout << "cargando globos" << endl;
			int posx, posy, speedx, speedy;
			file >> posx >> posy >> speedx >> speedy;

		}

		//carga las mariposas
		file >> count;

		for (int i = 0; i < count; i++) {
			cout << "cargando mariposas" << endl;
			int posx, posy, speedx, speedy;
			file >> posx >> posy >> speedx >> speedy;

		}
		//carga los premios
		file >> count;

		for (int i = 0; i < count; i++) {
			cout << "cargando flecha" << endl;
			int posx, posy, speedx, speedy;
			file >> posx >> posy >> speedx >> speedy;

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

void PlayState::addReward(Reward* reward)
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

void PlayState::addBalloon(Balloon* b)
{
	addGameObject(b);
	balloons_.push_back(b);
	Balloon::count++;
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
	clear();
	init();
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

}

void PlayState::clear()
{
	delete score_;
	score_ = nullptr;

	for (GameObject* obj : gObjects_) {
		delete obj;
		obj = nullptr;
	}

	gObjects_.clear();
	gObjectsToErase_.clear();
	evObjects_.clear();

	arrows_.clear();
	balloons_.clear();
	butterflies_.clear();
	rewards_.clear();

}

void PlayState::createButterflies(int n)
{
	for (int i = 0; i < n; i++) {
		Butterfly* b = new Butterfly(Vector2D(120 + rand() % (WIN_WIDTH - 220), rand() % WIN_HEIGHT), Vector2D(0.15, 0.15), 50, 50, app_->getTexture(TextureOrder::BUTTERFLY), this);
		addGameObject(b);
		butterflies_.push_back(b);
		Butterfly::count++;
	}
}

void PlayState::createBalloon()
{
	if (rand() % 50 == 0) {
		Balloon* b = new Balloon(Vector2D(100 + rand() % (WIN_WIDTH - 150), WIN_HEIGHT), Vector2D(0, 0.5), 400, 400, true, app_->getTexture(TextureOrder::BALLOONS), this);
		addBalloon(b);
	}
}

void PlayState::createReward(Reward* reward)
{

}

void PlayState::cleanMemory()
{
	
}
