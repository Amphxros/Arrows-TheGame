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

	virtual void saveToFile(std::ofstream& file) override;
	void loadFromFile(std::ifstream& file);
	inline bool isNonPunctured() { return non_punctured; }

	SDL_Rect* GetRect() {
		SDL_Rect dest;
		dest.x = pos_.getX();
		dest.y = pos_.getY();
		dest.w = width_ / 7;
		dest.h = height_ / 6;

		return &(dest);
	
	}

private:
	int color_;
	bool non_punctured= true;
	uint frame_ = 0;
};

