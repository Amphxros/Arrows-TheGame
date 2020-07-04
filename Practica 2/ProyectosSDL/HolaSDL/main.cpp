
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Game.h"
using namespace std;


int main(int argc, char* argv[]){
	Game g = Game();
	g.run();
	return 0;
}