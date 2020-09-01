#pragma once
#include <SDL.h>
#include "GameStateMachine.h"
#include <map>

using namespace std;

using uint = unsigned int;

//constantes
const uint FRAME_RATE = 50;
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint POINTS_PER_BALLON = 1;

//enum para las texturas
enum TextureOrder{
	BACKGROUND1,
	BACKGROUND2,
	BACKGROUND3,
	BACKGROUND4,
	BOW_1,
	BOW_2,
	BALLOONS,
	ARROW_1,
	ARROW_2,
	BUTTERFLY,
	REWARDS,
	BUBBLE,
	SCOREBOARD,
	BUTTON,
	BUTTON_START,
	BUTTON_LOAD,
	BUTTON_QUIT,
	BUTTON_RESUME,

	last
};
class SDLApp
{
public:
	//constructora
	SDLApp();
	//destructora
	~SDLApp();


	//bucle principal
	void run();
	
	//renderizado
	void render() const;
	
	//actualizado
	void update();
	
	//manejo de eventos
	void handleEvents();

	//devuelve la textura correspondiente
	inline Texture* getTexture(TextureOrder n) { return textures_.at(n); }

	inline uint getWidth() { return WIN_WIDTH; }
	inline uint getHeight() { return WIN_HEIGHT; }


	// callbacks
	static void quitApp(SDLApp* app);
	static void resumeApp(SDLApp* app);
	static void loadPlayState(SDLApp* app);
	static void savePlayState(SDLApp* app);
	static void toPlay(SDLApp* app);
	static void toPause(SDLApp* app);
	static void toMenu(SDLApp* app);

private:
	//ventana
	SDL_Window* window_=nullptr;
	//renderizado
	SDL_Renderer* renderer_=nullptr;
	//maquina de estados
	static GameStateMachine* stateMachine_;
	//booleano de continuado
	static bool exit_;
	//mapa de texturas
	std::map<TextureOrder, Texture*> textures_;

	//carga las texturas en el mapa
	void loadTextures();

};

