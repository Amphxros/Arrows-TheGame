#include "MenuButton.h"

MenuButton::MenuButton() :
	SDLGameObject(), EventHandler(), callback_(nullptr)
{
}

MenuButton::MenuButton(Vector2D pos, int width, int height, Texture* texture, GameState* state, CallBackOnClick* callback):
	SDLGameObject(pos,width,height,texture,state),EventHandler(), callback_(callback)
{
}

MenuButton::~MenuButton()
{
}

void MenuButton::render() const
{
	texture_->render(getDestRect());
}

void MenuButton::update()
{
}

bool MenuButton::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {

		SDL_Point p = { event.button.x, event.button.y };

		if (SDL_PointInRect(&p, &getDestRect())) {
			return true;
		}

	}
	if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
		SDL_Point p = { event.button.x, event.button.y };

		if (SDL_PointInRect(&p, &getDestRect())) {
			callback_(gamestate_->getApp());
			return true;
		}

	}
	return false;
}
