#pragma once
#include "ArrowsGameObject.h"
class Balloon: public ArrowsGameObject
{
public:
	static int count;

	Balloon();
	Balloon(Vector2D pos, Vector2D speed,double width, double height, bool punct, Texture* texture,GameState* state);
	virtual ~Balloon();

	virtual void render()const;
	virtual void update();

	virtual void saveToFile(std::ofstream& file);
	virtual void loadFromFile(std::ifstream file);
	inline bool isNonPunctured() { return non_punctured; }

	SDL_Rect* GetRect() {
		return new SDL_Rect{ (int)pos_.getY(),(int)pos_.getX(),(int)height_ / 7, (int)width_ / 6 };}

private:
	int color_;
	bool non_punctured= true;
	uint frame_ = 0;
};

