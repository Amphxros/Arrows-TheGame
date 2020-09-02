#include "ScoreBoard.h"
#include <string>
#include "SDLApp.h"

ScoreBoard::ScoreBoard():
	SDLGameObject(){ }

ScoreBoard::ScoreBoard(Vector2D pos, int width, int height, Texture* texture, Texture* arrow, GameState* state):
	SDLGameObject(pos,width,height,texture,state),arrow_texture(arrow), points_(0), arrows_(0) {}

void ScoreBoard::render() const
{
	for (int i = 0; i < arrows_; i++) {
		SDL_Rect dest;

		dest.x = WIN_WIDTH - 30 * (i%10);
		dest.w = 15;
		dest.h = 50;
	
		if (i < 10) {
			dest.y = 10;
		}
		else {
			dest.y = 60* (i/10);
		}
		arrow_texture->render(dest);

	}

	for (int i = 0; i < num_.size(); i++) {
		SDL_Rect dest;

		dest.x = pos_.getX() - width_ * i;
		dest.y = pos_.getY();
		dest.w = width_;
		dest.h = height_;

		texture_->renderFrame(dest, 0, num_[i]);
	}
}
void ScoreBoard::setPoints(int points)
{
	if (points > 0) {
		points_ = points;
	}
	else {
		points_ = 0;
	}
	num_.clear();
	int size = (char)to_string(points_).size();
	int score = points_;

	for (int i = 0; i < size; i++) {

		int j = score % 10;
		score /= 10;

		num_.push_back(j);
	}
}
