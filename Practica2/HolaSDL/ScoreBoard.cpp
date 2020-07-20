#include "ScoreBoard.h"
#include "Game.h"
ScoreBoard::ScoreBoard(): 
	GameObject(){}

ScoreBoard::ScoreBoard(Texture* score, Texture* arrow, int points, int arrows, Game* game):
	GameObject(), score_texture(score),arrow_texture(arrow),points_(points),arrows_(arrows) {}

ScoreBoard::~ScoreBoard()
{
	delete score_texture;
	delete arrow_texture;
}

void ScoreBoard::render()
{
	//render the points
	for (int i = 0; i < points.size(); i++) {
		SDL_Rect dest;

		dest.x = WIN_WIDTH - 50 * i;
		dest.y = 100;
		dest.w = 50;
		dest.h = 50;

		score_texture->renderFrame(dest, points[i],0);
	}
	
	//render the arrows left
	
	for (int i = 0; i < arrows_; i++) {
		SDL_Rect dest;

		dest.x = 50 * i;
		dest.y = 50;
		dest.w = 50;
		dest.h = 100;

		score_texture->renderFrame(dest, points[i],0);
	}
}

bool ScoreBoard::update()
{
	points.clear();
	int size = (char)to_string(points_).size();
	int p = points_;
	
	for(int i = size; i > 0; i--) {
		int aux = p % 10;
		p /= 10;
		points.push_back(aux);
	}
	
	return true;
}
