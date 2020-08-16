#include "PlayState.h"
#include "SDLApp.h"
#include "MenuButton.h"
#include <math.h>
#include <string>

PlayState::~PlayState()
{
}

void PlayState::init()
{
	Arrow::count = 0;
	Balloon::count = 0;
	Butterfly::count = 0;
	Reward::count = 0;
	// add scoreboard
	score_ = new ScoreBoard(Vector2D(WIN_WIDTH/2,0 ), 20, 20, app_->getTexture(TextureOrder::SCOREBOARD), app_->getTexture(TextureOrder::ARROW_2), this);
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
	app_->getTexture(TextureOrder::BACKGROUND2)->render(dest);
	GameState::render();
	score_->render(); //esto es para que se renderice encima del resto de objetos 
}

void PlayState::update()
{
	if (butterflies_.size() > 0) {
		GameState::update();
		cleanMemory();
		createBalloon();
	}
	else {
		cout << "all butterflies are dead" << endl;
		app_->quitApp(app_);
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

void PlayState::saveToFile(int seed)
{
	std::ofstream file;
	file.open(std::to_string(seed) + ".sav");
	if (file.is_open()) {
		//guardar nivel, puntuacion y flechas
		file << level << " " << score_->getPoints() << " " << score_->getArrows()<<endl;
		
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

		file >> count ;

		for (int i = 0; i < count; i++) {
			cout << "cargando flecha"<<endl;
		


		}

		//carga los globos
		//carga las mariposas
		//carga los premios



	}
	else {
		cout << "Cant load" << endl;
	}

}


void PlayState::addReward(Reward* reward)
{
	createReward(reward);
	Reward::count++;
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


void PlayState::createButterflies(int n)
{
	for (int i = 0; i < n; i++) {
		Butterfly* b = new Butterfly(Vector2D(120 + rand() % (WIN_WIDTH - 220), rand() % WIN_HEIGHT), Vector2D(0.15,0.15), 50, 50, app_->getTexture(TextureOrder::BUTTERFLY), this);
		addGameObject(b);
		butterflies_.push_back(b);
		Butterfly::count++;
	}
}

void PlayState::createBalloon()
{
	if (rand() % 150 == 0) {
		Balloon* b = new Balloon(Vector2D(100 + rand() % (WIN_WIDTH - 150), WIN_HEIGHT), Vector2D(0, 0.5), 400, 400, true, app_->getTexture(TextureOrder::BALLOONS), this);
		Balloon::count++;
		addGameObject(b);
		balloons_.push_back(b);
	}
}

void PlayState::createReward(Reward* reward)
{
	addGameObject(reward);
	Reward::count++;
	addEventHandler(reward);
	rewards_.push_back(reward);
}


bool PlayState::collisionWithBalloon(Balloon* balloon)
{
	bool col = false;
	auto it = arrows_.begin();

	while (it != arrows_.end() && !col) {

		SDL_Rect* dest_A = &(*it)->getCollisionRect();
		col = SDL_HasIntersection(&(balloon->getCollisionRect()),dest_A );
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


void PlayState::shoot(Arrow* arrow)
{
	Arrow::count++;
	addGameObject(arrow);
	arrows_.push_back(arrow);
	score_->setArrows(score_->getArrows() - 1);
}


void PlayState::cleanMemory()
{
	if (!gObjectsToErase_.empty()) {

		auto it = gObjectsToErase_.begin();

		while (it != gObjectsToErase_.end()) {
			auto git = gObjects_.begin();
			bool found = false;
			while (!found && git != gObjects_.end()) {

				if (dynamic_cast<EventHandler*>(**it)) {
					bool eventFounded = false;
					auto eit = evHandlers_.begin();
					while (!eventFounded && eit != evHandlers_.end())
					{
						auto aux = dynamic_cast<GameObject*>(*eit);
						if (*git == aux) {

							evHandlers_.erase(eit);
							eventFounded = true;
						}
						else eit++;
					}

				}

				else if (dynamic_cast<Arrow*>(*git)) {
					auto ait = arrows_.begin();
					bool arrowFounded = false;
					while (!arrowFounded && ait != arrows_.end())
					{
						if ((*git) == (*ait)) {
							arrows_.erase(ait);
							arrowFounded = true;
							found = true;
						}
						else ait++;
					}
				}

				else if (dynamic_cast<Balloon*>(*git)) {
					auto bit = balloons_.begin();
					bool bFounded = false;
					while (!bFounded && bit != balloons_.end())
					{
						if ((*git) == (*bit)) {
							balloons_.erase(bit);
							bFounded = true;
							found = true;
						}
						else bit++;
					}
				}
				
				else if (dynamic_cast<Butterfly*>(*git)) {
					auto bit = butterflies_.begin();
					bool bFounded = false;
					while (!bFounded && bit != butterflies_.end())
					{
						if ((*git) == (*bit)) {
							butterflies_.erase(bit);
							bFounded = true;
							found = true;
						}
						else bit++;
					}
				}
				
				if (dynamic_cast<Reward*>(*git)) {
					auto rit = rewards_.begin();
					bool rFounded = false;
					while (!rFounded && rit != rewards_.end())
					{
						if ((*git) == (*rit)) {
							rewards_.erase(rit);
							rFounded = true;
							found = true;
						}
						else rit++;
					}
				}
				auto auxIT = git;
				auto auxEIT = it;
				GameObject* gm = *git;
				git++;
				it++;
				gObjectsToErase_.erase(auxEIT);
				gObjects_.erase(auxIT);
				delete (gm);
				found = true;


			}
		
		}
		gObjectsToErase_.clear();
	}
}


void PlayState::deleteGameObject(std::list<GameObject*>::iterator go)
{
	gObjectsToErase_.push_back(go);
}

void PlayState::deleteArrow(std::list<GameObject*>::iterator it)
{
	//arrows_.remove(static_cast<Arrow*>((*it)));
	Arrow::count--;
	deleteGameObject(it);

}

void PlayState::deleteBalloon(std::list<GameObject*>::iterator it)
{
	//balloons_.remove(static_cast<Balloon*>((*it)));
	Balloon::count--;
	deleteGameObject(it);
}

void PlayState::deleteButterfly(std::list<GameObject*>::iterator it)
{
	//butterflies_.remove(static_cast<Butterfly*>((*it)));
	Butterfly::count--;
	deleteGameObject(it);
}

void PlayState::deleteReward(std::list<GameObject*>::iterator it, std::list<EventHandler*>::iterator ev)
{
	//rewards_.remove(static_cast<Reward*>((*it)));
	//evHandlers_.remove(static_cast<Reward*>((*ev)));
	Reward::count--;
	deleteGameObject(it);
}