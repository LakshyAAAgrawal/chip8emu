#include "../include/Keyboard.hpp"
#include <iostream>
#include <map>

bool Keyboard::isKeyDown(uint8_t key){
	// TODO
	std::map<int, uint8_t> key_map{
		{'1', 0x1},
		{'2', 0x2},
		{'3', 0x3},
		{'4', 0xc},
		{'q', 0x4},
		{'w', 0x5},
		{'e', 0x6},
		{'r', 0xd},
		{'a', 0x7},
		{'s', 0x8},
		{'d', 0x9},
		{'d', 0xe},
		{'z', 0xa},
		{'x', 0x0},
		{'c', 0xb},
		{'v', 0xf},
	};
	return false;
}

uint8_t Keyboard::waitAndGetKeypress(){
	// TODO
	std::map<int, uint8_t> key_map{
		{'1', 0x1},
		{'2', 0x2},
		{'3', 0x3},
		{'4', 0xc},
		{'q', 0x4},
		{'w', 0x5},
		{'e', 0x6},
		{'r', 0xd},
		{'a', 0x7},
		{'s', 0x8},
		{'d', 0x9},
		{'d', 0xe},
		{'z', 0xa},
		{'x', 0x0},
		{'c', 0xb},
		{'v', 0xf},
	};
	return 0;
}
