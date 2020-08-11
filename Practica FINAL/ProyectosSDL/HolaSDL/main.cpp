
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "SDLApp.h"
using namespace std;


int main(int argc, char* argv[]){
	//CrtSetDbgFlag(CRTDBG ALLOC MEM DF | CRTDBG LEAK CHECK DF);
	SDLApp app = SDLApp();
	app.run();
	return 0;
}