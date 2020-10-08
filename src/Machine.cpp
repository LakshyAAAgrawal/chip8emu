#include "../include/Machine.hpp"

Machine::Machine(){
	registers = new uint8_t[16];
	stack = new uint8_t[64];
	memory = new uint8_t[4096];
}
