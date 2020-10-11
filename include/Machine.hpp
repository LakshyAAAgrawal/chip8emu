#include <exception>
#include <stdint.h>
#include "../include/GraphicEngine.hpp"
#include <vector>
#include <random>

class ProgramLargerThanMemoryException: public std::exception {
  virtual const char* what() const throw()
  {
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
	uint16_t PC; // Program Counter
	void execute(uint16_t& opcode);
	uint8_t random_byte();
public:
	Machine();
	void setInst(std::vector<uint8_t>& prog, uint16_t start_addr);
	void runLoop();
};
