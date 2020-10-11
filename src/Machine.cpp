#include "../include/Machine.hpp"
#include <algorithm>
#include <functional>
#include <map>
#include <iostream>

Machine::Machine(){
	registers = std::vector<uint8_t>(16);
	stack = std::vector<uint8_t>(64);
	memory = std::vector<uint8_t>(4096);
	PC = 0x200;
}

uint8_t Machine::random_byte(){
	std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,255);
	return dist(rng);
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
		{0x0000, [this](uint16_t& op){}}, // To be ignored as per COWGOD
		{0x1000, [this](uint16_t& op){ PC = (op & 0x0fff);}}, // JP addr
		{0x2000, [this](uint16_t& op){ SP++; stack[SP] = PC; PC = (op & 0x0fff);}}, // CALL addr
		{0x3000, [this](uint16_t& op){ PC += ((registers[(op & 0x0f00)>>8] == (op & 0x00ff))? 2: 0);}}, // 3xkk - SE Vx, byte
		{0x4000, [this](uint16_t& op){ PC += ((registers[(op & 0x0f00)>>8] != (op & 0x00ff))? 2: 0);}}, // 4xkk - SNE Vx, byte
		{0x6000, [this](uint16_t& op){ registers[(op & 0x0f00)>>8] = (op & 0x00ff);}}, // 6xkk - LD Vx, byte
		{0x7000, [this](uint16_t& op){ registers[(op & 0x0f00)>>8] += (op & 0x00ff);}}, // 7xkk - ADD Vx, byte
		{0xa000, [this](uint16_t& op){ I = (op & 0x0fff);}}, // Annn - LD I, addr
		{0xb000, [this](uint16_t& op){ PC = registers[0] + (op & 0x0fff);}}, // Bnnn - JP V0, addr
		{0xc000, [this](uint16_t& op){ registers[(op & 0x0f00)>>8] = (op & 0x00ff) & random_byte();}}, // Cxkk - RND Vx, byte
		{0xd000, [this](uint16_t& op){}} // TODO - Dxyn - DRW Vx, Vy, nibble
	};

	auto it = direct_match.find(opcode);
	if(it != direct_match.end()){}
	else if((it = first_third_fourth_match.find(opcode & 0xf0ff)) != first_third_fourth_match.end()){}
	else if((it = first_fourth_match.find(opcode & 0xf00f)) != first_fourth_match.end()){}
	else if((it = first_match.find(opcode & 0xf000)) != first_match.end()){}

	if(it != first_match.end()) (it->second)(opcode);
	else std::cout << "No match found for " << std::hex << (int) opcode << "\n";
}

void Machine::runLoop(){
	while(true){
		uint16_t opcode = (memory[PC]<<8) | (memory[PC+1]);
		execute(opcode);
	}
}
