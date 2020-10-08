#include <stdint.h>
#include "../include/GraphicEngine.hpp"

class Machine{
private:
	uint8_t * registers; // V0-VF
	uint8_t * memory; // Memory
	uint16_t IR; // Index register
	uint8_t * stack; // Stack
	uint8_t SP; // Stack Pointer
	uint8_t DT; // Delay Timer
	uint8_t ST; // Sound Timer
	GraphicEngine ge; // Holds Graphics and framebuffer
	uint16_t PC; // Program Counter
public:
	Machine();
};
