#include "../include/Game.hpp"
#include <stdint.h>
#include <iostream>

using namespace std;

uint8_t * loadFile(char * filename){
	return new uint8_t[6000];
}

int main(int argc, char ** argv){
	Game game;
	uint8_t * prog = loadFile(argv[1]);
	game.loadInstructions(prog);
	game.runLoop();
	return 0;
}
