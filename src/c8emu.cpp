#include "../include/Machine.hpp"
#include <stdint.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>

void loadFile(const std::string& filename, std::vector<uint8_t>& prog){
	// From https://stackoverflow.com/questions/5420317/reading-and-writing-binary-file
	std::ifstream input(filename, std::ios::binary);
	for(char c: std::vector<char>(std::istreambuf_iterator<char>(input), {})){
		prog.push_back(c);
	}
}

int main(int argc, char ** argv){
	Machine machine;

	// Load Instructions
	std::vector<uint8_t> * prog = new std::vector<uint8_t>();
	loadFile(argv[1], *prog);
	machine.setInst(*prog, 0x200);
	delete prog;

	// Load Sprites
	std::vector<uint8_t> * sprites = new std::vector<uint8_t>();
	loadFile("../res/sprites.bin", *prog);
	machine.setInst(*sprites, 0x000);
	delete sprites;

	// Begin instruction fetch-execute-increment cycle
	machine.runLoop();
	
	return 0;
}
