#pragma once
#include <SDL.h>
#include "GameStateMachine.h"
#include <map>
#include "checkML.h"

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
	//devuelve la textura correspondiente
	inline Texture* getTexture(TextureOrder n) { return textures_.at(n); }

	inline uint getWidth() { return WIN_WIDTH; }
	inline uint getHeight() { return WIN_HEIGHT; }

	//renderizado
	void render() const;
	//actualizado
	void update();
	//manejo de eventos
	void handleEvents();


	// callbacks
	static void quitApp(SDLApp* app);
	static void resumeApp(SDLApp* app);
	static void loadPlayState(SDLApp* app);
	static void savePlayState(SDLApp* app);
	static void toPlay(SDLApp* app);
	static void toPause(SDLApp* app);
	static void toMenu(SDLApp* app);

private:
	
	SDL_Window* window_=nullptr;		//ventana
	SDL_Renderer* renderer_=nullptr;	//renderizado
	
	static GameStateMachine* stateMachine_;		//maquina de estados
	static bool exit_;		//booleano para el bucle principal
	
	std::map<TextureOrder, Texture*> textures_;		//mapa de texturas

	//carga las texturas en el mapa
	void loadTextures();

};

