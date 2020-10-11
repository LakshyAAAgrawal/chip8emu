#include "../include/Machine.hpp"
#include <stdint.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>

void loadFile(char * filename, std::vector<uint8_t>& prog){
	// From https://stackoverflow.com/questions/5420317/reading-and-writing-binary-file
	std::ifstream input(filename, std::ios::binary);
	for(char c: std::vector<char>(std::istreambuf_iterator<char>(input), {})){
		prog.push_back(c);
	}
}

int main(int argc, char ** argv){
	Machine machine;
	std::vector<uint8_t> * prog = new std::vector<uint8_t>();
	loadFile(argv[1], *prog);
	machine.setInst(*prog, 0x200);
	delete prog;
	machine.runLoop();
	return 0;
}
