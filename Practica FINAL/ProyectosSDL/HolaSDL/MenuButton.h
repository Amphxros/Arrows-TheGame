#pragma once

#include "SDLGameObject.h"
#include "EventHandler.h"
#include "SDLApp.h"

using CallBackOnClick = void(SDLApp * app);
class MenuButton :
	public SDLGameObject, public EventHandler
{
public:
	MenuButton();
	MenuButton(Vector2D pos, int width, int height, Texture* texture, GameState* state, CallBackOnClick* callback);
	virtual ~MenuButton();

	virtual void render() const;
	virtual void update();
	virtual bool handleEvent(SDL_Event& event);

protected:
	CallBackOnClick* callback_;
};

