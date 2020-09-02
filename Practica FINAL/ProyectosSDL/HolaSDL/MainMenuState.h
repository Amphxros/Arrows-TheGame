#pragma once
#include "GameState.h"

#include "checkML.h"
class MainMenuState :
	public GameState
{
public:
	MainMenuState(SDLApp* app);
	virtual ~MainMenuState();

	void init();
	virtual void render() const;
	virtual void update();
	virtual void handleEvents(SDL_Event& event);



};

