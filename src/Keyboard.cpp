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
	while(kb.kbhit()){
		int ch = kb.getch();
		// std::cout << (int) ch << " Pressed" << "\n";
		if(ch == 'l'){
			std::exit(0);
		}
		auto it = key_map.find(ch);
		//while(kb.kbhit()) kb.getch();
		if(it != key_map.end() && (it->second == key)){
			return true;
		}
		//return false;
	}
	return false;
}

uint8_t Keyboard::waitAndGetKeypress(){
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
	while(true){
		while(kb.kbhit()){
			int ch = kb.getch();
			// std::cout << (int) ch << " Pressed" << "\n";
			if(ch == 'l'){
				std::exit(0);
			}
			auto it = key_map.find(ch);
			if(it != key_map.end()){
				while(kb.kbhit()) kb.getch();
				return it->second;
			}
		}
	}
	return 0;
}
