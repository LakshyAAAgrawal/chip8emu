#include "../include/Machine.hpp"
#include <algorithm>
#include <functional>
#include <map>

Machine::Machine(){
	registers = std::vector<uint8_t>(16);
	stack = std::vector<uint8_t>(64);
	memory = std::vector<uint8_t>(4096);
	PC = 0x200;
}

void Machine::setInst(std::vector<uint8_t>& prog, uint16_t start_addr){
	if((int)start_addr + (int)prog.size() - 1 < 4096){
		std::copy(prog.begin(), prog.end(), memory.begin() + start_addr);
	}else{
		throw new ProgramLargerThanMemoryException();
	}
}

void Machine::execute(uint16_t& opcode){
	std::map<uint16_t, std::function<void(uint16_t&)>> direct_match{
		{0x00e0, [this](uint16_t& op){ge.cls();}},
		{0x00ee, [this](uint16_t& op){PC = stack[SP]; SP--;}},
	};
	std::map<uint16_t, std::function<void(uint16_t&)>> first_third_fourth_match{
		{0xe09e, [this](uint16_t& op){}},
		{0xe0a1, [this](uint16_t& op){}},
		{0xf007, [this](uint16_t& op){}},
		{0xf00a, [this](uint16_t& op){}},
		{0xf015, [this](uint16_t& op){}},
		{0xf018, [this](uint16_t& op){}},
		{0xf01e, [this](uint16_t& op){}},
		{0xf029, [this](uint16_t& op){}},
		{0xf033, [this](uint16_t& op){}},
		{0xf055, [this](uint16_t& op){}},
		{0xf065, [this](uint16_t& op){}}
	};
	std::map<uint16_t, std::function<void(uint16_t&)>> first_fourth_match{
		{0x5000, [this](uint16_t& op){}},
		{0x8000, [this](uint16_t& op){}},
		{0x8001, [this](uint16_t& op){}},
		{0x8002, [this](uint16_t& op){}},
		{0x8003, [this](uint16_t& op){}},
		{0x8004, [this](uint16_t& op){}},
		{0x8005, [this](uint16_t& op){}},
		{0x8006, [this](uint16_t& op){}},
		{0x8007, [this](uint16_t& op){}},
		{0x800e, [this](uint16_t& op){}},
		{0x9000, [this](uint16_t& op){}},
		{0x8000, [this](uint16_t& op){}},
	};
	std::map<uint16_t, std::function<void(uint16_t&)>> first_match{
		{0x0000, [this](uint16_t& op){}},
		{0x1000, [this](uint16_t& op){}},
		{0x2000, [this](uint16_t& op){}},
		{0x3000, [this](uint16_t& op){}},
		{0x4000, [this](uint16_t& op){}},
		{0x6000, [this](uint16_t& op){}},
		{0x7000, [this](uint16_t& op){}},
		{0xa000, [this](uint16_t& op){}},
		{0xb000, [this](uint16_t& op){}},
		{0xc000, [this](uint16_t& op){}},
		{0xd000, [this](uint16_t& op){}},
	};
}

void Machine::runLoop(){
	while(true){
		uint16_t opcode = (memory[PC]<<8) | (memory[PC+1]);
		execute(opcode);
	}
}
