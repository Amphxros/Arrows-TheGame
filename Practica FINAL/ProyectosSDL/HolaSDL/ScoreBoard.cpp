#include "ScoreBoard.h"

ScoreBoard::ScoreBoard():
	SDLGameObject()
{
}

ScoreBoard::ScoreBoard(Vector2D pos, int width, int height, Texture* texture, Texture* arrow, GameState* state):
	SDLGameObject(pos,width,height,texture,state),arrow_texture(arrow), points_(0), arrows_(0) {}

void ScoreBoard::render() const
{
	for (int i = 0; i < arrows_; i++) {
		SDL_Rect dest;

		dest.x = 0 + 30 * i;
		dest.y = 10;
		dest.w = 30;
		dest.h = 100;

		arrow_texture->render(dest);

	}
}

void ScoreBoard::update()
{
}
