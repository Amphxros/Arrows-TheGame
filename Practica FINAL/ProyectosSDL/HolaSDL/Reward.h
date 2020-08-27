#pragma once
#include "ArrowsGameObject.h"
#include "EventHandler.h"
class Reward :
	public ArrowsGameObject, public EventHandler
{
public:
	static int count;

	Reward();
	Reward(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, Texture* textureB, GameState* state);
	~Reward();

	virtual void render()const;
	virtual void update();
	virtual bool handleEvent(SDL_Event& event);


	virtual void saveToFile(std::ofstream& file);
	virtual void loadFromFile(std::ifstream file);

	inline bool getBubbled() { return bubbled_; }

private:
	bool bubbled_;
	bool clicked_;
	int color_;
	int frame_; 
	Texture* texture_B;
};

