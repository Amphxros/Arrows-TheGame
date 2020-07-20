
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"
#include "checkML.h"
#include <iostream>

using namespace std;

using uint = unsigned int;


int main(int argc, char* argv[]){

	Game g = Game();
	g.run();

	return 0;
}