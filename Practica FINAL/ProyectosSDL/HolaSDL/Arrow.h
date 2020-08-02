#pragma once
#include "ArrowsGameObject.h"
class SDLApp;
class Arrow: public ArrowsGameObject
{
public:
	static int count;

	Arrow();
	Arrow(Vector2D pos, Vector2D speed, double width, double height, Texture* texture, GameState* state);
	virtual ~Arrow();
	
    virtual void render()const;
	virtual void update();
	
	inline int getNumHits() { return nHits_; };
	void setNumHits(int hits) { nHits_ = hits; };

	void setPos(Vector2D v);	

	SDL_Rect* GetPoint();
	SDL_Rect getCollisionRect();

	private:
		int nHits_;
};

