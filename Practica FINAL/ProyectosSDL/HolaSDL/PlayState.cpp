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
	num_arrows_ = 0;
	num_balloons_ = 0;
	num_butterflies_ = 0;
	num_rewards_ = 0;
}

void PlayState::createGame()
{
	background_ = app_->getTexture(TextureOrder::BACKGROUND2);
	createScoreBoard();
	createNewBow();
	//add n butterflies
	createButterflies(10);
}

void PlayState::render() const
{
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = app_->getWidth();
	dest.h = app_->getHeight();
	background_->render(dest);
	GameState::render();
	score_->render(); //esto es para que se renderice encima del resto de objetos 
}

void PlayState::update()
{
	if (num_butterflies_!= 0 && score_->getArrows()>0) {
		GameState::update();
		createBalloon();
		deleteObjects();
	}
	else {
		if (num_butterflies_ == 0) {
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
		
		//flechas
		file << num_arrows_ << endl;
		cout << num_arrows_<< " " << arrows_.size()<<endl;

		for (Arrow* arrow : arrows_) {
			arrow->saveToFile(file);
		}

		//globos
		file << num_balloons_ << endl;
		cout << num_balloons_ << " " << balloons_.size()<<endl;

		for (Balloon* b : balloons_) {
			if (b->isNonPunctured()) {
				b->saveToFile(file);
			}
		}

		//mariposas
		file << num_butterflies_ << endl;
		cout << num_butterflies_ << " " << butterflies_.size()<<endl;
		for (Butterfly* b : butterflies_) {
			b->saveToFile(file);
		}

		//premios
		file << num_rewards_ << endl;
		cout << num_rewards_ << " " << rewards_.size() << endl;

		for (Reward* r : rewards_) {
			r->saveToFile(file);
		}

		cout<< endl;

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
		score_ = new ScoreBoard(Vector2D(app_->getWidth() / 2, 0), 20, 20, app_->getTexture(TextureOrder::SCOREBOARD), app_->getTexture(TextureOrder::ARROW_2), this);
		addGameObject(score_);

		int score, level_,arrow;

		file >> level_ >> score >> arrow;
		level = level_;
		setBackground(level);
		cout << endl;
		//carga el arco
		bow_ = new Bow(Vector2D(0,0), Vector2D(0,0), 100, 150, app_->getTexture(TextureOrder::BOW_1), app_->getTexture(TextureOrder::BOW_2), app_->getTexture(TextureOrder::ARROW_1), this);
		bow_->loadFromFile(file);
		addGameObject(bow_);
		addEventHandler(bow_);
		
		//carga las flechas
		int arrows=-1;
		file >> arrows;
		cout << endl;
		for (int i = 0; i < arrows; i++) {
			Arrow* a= new Arrow(Vector2D(0, 0), Vector2D(0, 0), (double)100, (double)31,app_->getTexture(TextureOrder::ARROW_1), this);
			a->loadFromFile(file);
			shoot(a);
		}
		score_->setPoints(score);
		score_->setArrows(arrow);
		
		//carga los globos
		int ballons=-1;
		file >> ballons;
		cout << endl;
		for (int i = 0; i < ballons; i++) {
			Balloon* b = new Balloon(Vector2D(0, 0), Vector2D(0, 0), 400, 400, false, app_->getTexture(TextureOrder::BALLOONS), this);
			b->loadFromFile(file);
			addNewBalloon(b);
		}

		//carga las mariposas
		int butterflies=-1;
		file >> butterflies;
		cout << endl;
		for (int i = 0; i < butterflies; i++) {
		
			Butterfly* b = new Butterfly(Vector2D(120 + rand() % (app_->getWidth() - 220), rand() % app_->getHeight()), Vector2D(0.15, 0.15), 50, 50, app_->getTexture(TextureOrder::BUTTERFLY), this);
			b->loadFromFile(file);
			addNewButterfly(b);
		}

		//carga los premios
		int rewards;
		file >> rewards;
		cout << endl;
		for (int i = 0; i < rewards; i++) {
			Reward* r = new Reward(Vector2D(0,0), Vector2D(0,0), 40, 40, app_->getTexture(TextureOrder::REWARDS), app_->getTexture(TextureOrder::BUBBLE), this);
			r->loadFromFile(file);
			addNewReward(r);
		}

		file.close();
	}
	else {
		throw domain_error("archivo corrupto");
	}
}

void PlayState::deleteObjects()
{
	if (!gObjectsToErase_.empty()) {
	
	std::list<std::list<GameObject*>::iterator>::iterator er_it = gObjectsToErase_.begin();
	
	while (er_it != gObjectsToErase_.end()) {
	
		auto g_it = gObjects_.begin();
		bool found = false;
	
		while (!found && g_it != gObjects_.end()) {
			if ((*er_it) == (g_it)) {
	
				if (dynamic_cast<EventHandler*>(*g_it)) {
					bool eventFounded = false;
					auto ev_it = evObjects_.begin();
					while (!eventFounded && ev_it != evObjects_.end())
					{
						auto aux = dynamic_cast<GameObject*>(*ev_it);
						if (*g_it == aux) {
							auto aux_it = ev_it;
							evObjects_.remove(*aux_it);
							eventFounded = true;
							found = true;
						}
						else ev_it++;
					}
				}
	
				auto aux_it = g_it;
				auto aux_e_it = er_it;
				GameObject* gm = *g_it;
				er_it++;
				g_it++;
				gObjectsToErase_.erase(aux_e_it);
				gObjects_.erase(aux_it);
				delete (gm);
				found = true;
				}
			else g_it++;
			}
	
		}
	gObjectsToErase_.clear();
	}
}

void PlayState::shoot(Arrow* arrow)
{
	if (score_->getArrows() > 0) {
		num_arrows_++;
		score_->setArrows(score_->getArrows() - 1);
		addGameObject(arrow);
		arrows_.push_back(arrow);
	}
}

void PlayState::addNewReward(Reward* reward)
{
	num_rewards_++;
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
	num_balloons_++;
	addGameObject(b);
	balloons_.push_back(b);

}

void PlayState::addNewButterfly(Butterfly* b)
{
	num_butterflies_++;
	addGameObject(b);
	butterflies_.push_back(b);
}

void PlayState::deleteGameObject(std::list<GameObject*>::iterator go)

{
	killObject(go);
}

void PlayState::createNewBow()
{
	//add bow
	bow_ = new Bow(Vector2D(0, 0), Vector2D(0, 5), 100, 150, app_->getTexture(TextureOrder::BOW_1), app_->getTexture(TextureOrder::BOW_2), app_->getTexture(TextureOrder::ARROW_1), this);
	addGameObject(bow_);
	addEventHandler(bow_);
}

void PlayState::createScoreBoard()
{
	// add scoreboard
	score_ = new ScoreBoard(Vector2D(app_->getWidth() / 2, 0), 20, 20, app_->getTexture(TextureOrder::SCOREBOARD), app_->getTexture(TextureOrder::ARROW_2), this);
	score_->setPoints(0);
	score_->setArrows(10);
}

void PlayState::deleteArrow(std::list<GameObject*>::iterator it)
{
	num_arrows_--;
	arrows_.remove(static_cast<Arrow*>((*it)));
	killObject(it);
}

void PlayState::deleteBalloon(std::list<GameObject*>::iterator it)
{
	num_balloons_--;
	balloons_.remove(static_cast<Balloon*>((*it)));
	killObject(it);
}

void PlayState::deleteButterfly(std::list<GameObject*>::iterator it)
{
	num_butterflies_--;
	butterflies_.remove(static_cast<Butterfly*>((*it)));
	killObject(it);
}

void PlayState::deleteReward(std::list<GameObject*>::iterator it, std::list<EventHandler*>::iterator ev)
{
	num_rewards_--;
	rewards_.remove(static_cast<Reward*>((*it)));
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
		it++;

	}
	return col;
}

void PlayState::nextLevel()
{
	level++;
	int score = score_->getPoints();
	delete score_;
	//clear();
	createScoreBoard();
	setBackground(level);
	score_->setPoints(score);
	score_->setArrows(10);
}

void PlayState::clear()
{
	delete score_;
	score_ = nullptr;
	
	for (auto i = gObjects_.begin(); i != gObjects_.end(); i++)
		gObjects_.erase(i);

	for (auto i = evObjects_.begin(); i != evObjects_.end(); i++)
		evObjects_.remove(static_cast<EventHandler*>(*i));

	for (auto i = arrows_.begin(); i != arrows_.end(); i++)
		arrows_.remove(static_cast<Arrow*>(*i));
	
	for (auto i = balloons_.begin(); i != balloons_.end(); i++)
		balloons_.remove(static_cast<Balloon*>(*i));
	
	for (auto i = butterflies_.begin(); i != butterflies_.end(); i++)
		butterflies_.remove(static_cast<Butterfly*>(*i));
	
	for (auto i = rewards_.begin(); i != rewards_.end(); i++)
		rewards_.remove(static_cast<Reward*>(*i));
	
	gObjects_.clear();
	arrows_.clear();
	balloons_.clear();
	evObjects_.clear();
	butterflies_.clear();
	rewards_.clear();
	gObjectsToErase_.clear();
}

void PlayState::createButterflies(int n)
{
	for (int i = 0; i < n; i++) {
		Butterfly* b = new Butterfly(Vector2D(120 + rand() % (app_->getWidth() - 220), rand() % app_->getHeight()), Vector2D(0.15, 0.15), 50, 50, app_->getTexture(TextureOrder::BUTTERFLY), this);
		addNewButterfly(b);
	}
}

void PlayState::createBalloon()
{
	if (rand() % 50 == 0) {
		Balloon* b = new Balloon(Vector2D(100 + rand() % (app_->getWidth() - 150), app_->getHeight()), Vector2D(0, 0.5), 400, 400, true, app_->getTexture(TextureOrder::BALLOONS), this);
		addNewBalloon(b);
	}
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
