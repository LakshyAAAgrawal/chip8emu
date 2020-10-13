#include "../include/Keyboard.hpp"
#include <iostream>
#include <map>

Keyboard::Keyboard(){
	key_map = std::map<int, uint8_t>{
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
		{'f', 0xe},
		{'z', 0xa},
		{'x', 0x0},
		{'c', 0xb},
		{'v', 0xf},
	};
	pressed_keys = std::vector<int>(16, 0);
}

void Keyboard::update_pressed_keys(){
	if(kb.kbhit()){
		int ch = kb.getch();
		if(ch == 'l') exit(0);
		auto it = key_map.find(ch);
		if(it != key_map.end()){
			pressed_keys[it->second] += 1;
		}
	}
	// for(int i = 0; i < 16; ++i) pressed_keys[i] = (pressed_keys[i] > 0) ? pressed_keys[i]-1 : 0;
}

bool Keyboard::isKeyDown(uint8_t key){
	// TODO
	if(pressed_keys[key] > 0){
		pressed_keys[key] = 0;
		return true;
	}
	else return false;
}

uint8_t Keyboard::waitAndGetKeypress(){
	do{
		for(int i = 0; i < 16; ++i){
			if(pressed_keys[i] > 0){
				pressed_keys[i] = 0;
				return i;
			}
		}
		update_pressed_keys();
	}while(true);
	
	return 0;
}
