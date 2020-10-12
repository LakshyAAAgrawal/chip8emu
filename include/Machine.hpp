#include <exception>
#include <stdint.h>
#include <vector>
#include <random>
#include <chrono>

#include "../include/GraphicEngine.hpp"
#include "../include/Keyboard.hpp"

class ProgramLargerThanMemoryException: public std::exception {
	virtual const char* what() const throw(){
		return "The passed program is larger than the memory";
	}
};

class Machine{
private:
	std::vector<uint8_t> registers; // V0-VF
	std::vector<uint8_t> memory; // Memory
	uint16_t I; // Index register
	std::vector<uint8_t> stack; // Stack
	uint8_t SP; // Stack Pointer
	uint8_t DT; // Delay Timer
	uint8_t ST; // Sound Timer
	GraphicEngine ge; // Holds Graphics and frame buffer
	Keyboard kb; // presents Keyboard related functions
	uint16_t PC; // Program Counter
	std::chrono::steady_clock::time_point last_tick;
	
	// Methods
	void execute(uint16_t& opcode);
	uint8_t random_byte();
	void update_sound_timer(const std::chrono::steady_clock::time_point& now);
	void update_delay_timer(const std::chrono::steady_clock::time_point& now);
	void print_machine_state();
public:
	Machine();
	void setInst(std::vector<uint8_t>& prog, uint16_t start_addr);
	void runLoop();
};
