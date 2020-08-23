#pragma once
#include "GameState.h"
class PauseState :
	public GameState
{
public:
	PauseState(SDLApp* app) :
		GameState(app) {
		init();
	};
	virtual ~PauseState();

	void init();
	virtual void render() const;
	virtual void update();
	virtual void handleEvents(SDL_Event& event);

	inline virtual State getState() { return State::PAUSE; }
};

