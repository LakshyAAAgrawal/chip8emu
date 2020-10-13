#include "../include/Machine.hpp"
#include <algorithm>
#include <functional>
#include <map>
#include <iostream>
#include <chrono>
#include <thread>

Machine::Machine(){
	registers = std::vector<uint8_t>(16, 0);
	stack = std::vector<uint16_t>(32, 0);
	memory = std::vector<uint8_t>(4096, 0);
	PC = 0x200;
	last_tick = std::chrono::steady_clock::now();
	I = 0;
	SP = 0;
	DT = 0;
	ST = 0;
}

uint8_t Machine::random_byte(){
	// From https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
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
		{0x00e0, [this](uint16_t& op){ ge.cls();}},
		{0x00ee, [this](uint16_t& op){ PC = stack[--SP]; }},
	};
	std::map<uint16_t, std::function<void(uint16_t&)>> first_third_fourth_match{
		{0xe09e, [this](uint16_t& op){ if(kb.isKeyDown(registers[(op & 0x0f00)>>8])) PC += 2; }}, // Ex9E - SKP Vx
		{0xe0a1, [this](uint16_t& op){ if(!kb.isKeyDown(registers[(op & 0x0f00)>>8])) PC += 2; }}, // ExA1 - SKNP Vx
		{0xf007, [this](uint16_t& op){ registers[(op & 0x0f00)>>8] = DT; }}, // Fx07 - LD Vx, DT
		{0xf00a, [this](uint16_t& op){ registers[(op & 0x0f00)>>8] = kb.waitAndGetKeypress(); }}, // Fx0A - LD Vx, K
		{0xf015, [this](uint16_t& op){ DT = registers[(op & 0x0f00)>>8]; }}, // Fx15 - LD DT, Vx
		{0xf018, [this](uint16_t& op){ ST = registers[(op & 0x0f00)>>8]; }}, // Fx18 - LD ST, Vx
		{0xf01e, [this](uint16_t& op){ I += (uint16_t)registers[(op & 0x0f00)>>8]; }}, // Fx1E - ADD I, Vx
		{0xf029, [this](uint16_t& op){ I = ((uint16_t)registers[(op & 0x0f00)>>8])*5; }}, // Fx29 - LD F, Vx
		{0xf033, [this](uint16_t& op){ // Fx33 - LD B, Vx
			memory[I] = (registers[(op & 0x0f00)>>8] / 100);
			memory[I+1] = ((registers[(op & 0x0f00)>>8]%100) / 10);
			memory[I+2] = ((registers[(op & 0x0f00)>>8]%10) / 1);
		}},

		// TODO - Check both the following instructions whether I = I+X+1 http://mattmik.com/files/chip8/mastering/chip8.html
		{0xf055, [this](uint16_t& op){ // Fx55 - LD [I], Vx
			std::copy(registers.begin(), registers.begin() + ((op & 0x0f00)>>8) + 1, memory.begin() + I);
			// I += (uint16_t)((op & 0x0f00)>>8) + 1;
		}},
		{0xf065, [this](uint16_t& op){ // Fx65 - LD Vx, [I]
			std::copy(memory.begin() + I, memory.begin() + I + ((op & 0x0f00)>>8) + 1, registers.begin());
			// I += (uint16_t)((op & 0x0f00)>>8) + 1;
		}}
	};
	std::map<uint16_t, std::function<void(uint16_t&)>> first_fourth_match{
		{0x5000, [this](uint16_t& op){ PC += ((registers[(op & 0x0f00)>>8] == registers[(op & 0x00f0)>>4])? 2: 0); }}, // 5xy0 - SE Vx, Vy
		{0x8000, [this](uint16_t& op){ registers[(op & 0x0f00)>>8] = registers[(op & 0x00f0)>>4]; }}, // 8xy0 - LD Vx, Vy
		{0x8001, [this](uint16_t& op){ registers[(op & 0x0f00)>>8] = registers[(op & 0x00f0)>>4] | registers[(op & 0x0f00)>>8]; }}, // 8xy1 - OR Vx, Vy
		{0x8002, [this](uint16_t& op){ registers[(op & 0x0f00)>>8] = registers[(op & 0x00f0)>>4] & registers[(op & 0x0f00)>>8]; }}, // 8xy2 - AND Vx, Vy
		{0x8003, [this](uint16_t& op){ registers[(op & 0x0f00)>>8] = registers[(op & 0x00f0)>>4] ^ registers[(op & 0x0f00)>>8]; }}, // 8xy3 - XOR Vx, Vy
		{0x8004, [this](uint16_t& op){ // 8xy4 - ADD Vx, Vy
			registers[(op & 0x0f00)>>8] = registers[(op & 0x00f0)>>4] + registers[(op & 0x0f00)>>8]; // TEST
			registers[0xf] = ((0xff - registers[(op & 0x00f0)>>4]) < registers[(op & 0x0f00)>>8])? 1 : 0;
		}},
		{0x8005, [this](uint16_t& op){ // 8xy5 - SUB Vx, Vy
			registers[0xf] = (registers[(op & 0x0f00)>>8] > registers[(op & 0x00f0)>>4]) ? 1 : 0;
			registers[(op & 0x0f00)>>8] = registers[(op & 0x0f00)>>8] - registers[(op & 0x00f0)>>4];
		}},
		{0x8006, [this](uint16_t& op){ // 8xy6 - SHR Vx {, Vy}
			registers[0xf] = (registers[(op & 0x0f00)>>8] & 0x1);
			registers[(op & 0x0f00)>>8] >>= 1;
		}},
		{0x8007, [this](uint16_t& op){ // 8xy7 - SUBN Vx, Vy
			registers[0xf] = (registers[(op & 0x0f00)>>8] < registers[(op & 0x00f0)>>4]) ? 1 : 0;
			registers[(op & 0x0f00)>>8] = registers[(op & 0x00f0)>>4] - registers[(op & 0x0f00)>>8];
		}},
		{0x800e, [this](uint16_t& op){ registers[0xf] = (registers[(op & 0x0f00)>>8] & 0x80) >> 7; registers[(op & 0x0f00)>>8] <<= 1; }}, // 8xyE - SHL Vx {, Vy}
		{0x9000, [this](uint16_t& op){ PC += ((registers[(op & 0x0f00)>>8] != registers[(op & 0x00f0)>>4])? 2: 0); }}, // 9xy0 - SNE Vx, Vy
		{0x8000, [this](uint16_t& op){ registers[(op & 0x0f00)>>8] = registers[(op & 0x00f0)>>4]; }}, // 8xy0 - LD Vx, Vy
	};
	std::map<uint16_t, std::function<void(uint16_t&)>> first_match{
		{0x0000, [this](uint16_t& op){}}, // To be ignored as per COWGOD
		{0x1000, [this](uint16_t& op){ PC = (op & 0x0fff); }}, // JP addr
		{0x2000, [this](uint16_t& op){ stack[SP++] = PC; PC = (op & 0x0fff); }}, // CALL addr
		{0x3000, [this](uint16_t& op){ PC += ((registers[(op & 0x0f00)>>8] == (op & 0x00ff))? 2: 0); }}, // 3xkk - SE Vx, byte
		{0x4000, [this](uint16_t& op){ PC += ((registers[(op & 0x0f00)>>8] != (op & 0x00ff))? 2: 0); }}, // 4xkk - SNE Vx, byte
		{0x6000, [this](uint16_t& op){ registers[(op & 0x0f00)>>8] = (op & 0x00ff); }}, // 6xkk - LD Vx, byte
		{0x7000, [this](uint16_t& op){ registers[(op & 0x0f00)>>8] += (op & 0x00ff); }}, // 7xkk - ADD Vx, byte
		{0xa000, [this](uint16_t& op){ I = (op & 0x0fff); }}, // Annn - LD I, addr
		{0xb000, [this](uint16_t& op){ PC = (uint16_t)registers[0] + (op & 0x0fff); }}, // Bnnn - JP V0, addr
		{0xc000, [this](uint16_t& op){ registers[(op & 0x0f00)>>8] = (op & 0x00ff) & random_byte(); }}, // Cxkk - RND Vx, byte
		{0xd000, [this](uint16_t& op){ // TODO - Dxyn - DRW Vx, Vy, nibble
			// Need to understand why will 1 not be added to second argument
			registers[0xf] = ge.draw_sprite(memory.begin() + I, memory.begin() + I + (op & 0x000f), registers[(op & 0x0f00)>>8] % 0x40, registers[(op & 0x00f0)>>4] % 0x20);
		}}
	};

	auto it = direct_match.find(opcode);
	if(it != direct_match.end()){}
	else if((it = first_third_fourth_match.find(opcode & 0xf0ff)) != first_third_fourth_match.end()){}
	else if((it = first_fourth_match.find(opcode & 0xf00f)) != first_fourth_match.end()){}
	else if((it = first_match.find(opcode & 0xf000)) != first_match.end()){}

	if(it != first_match.end()) (it->second)(opcode);
	else {
		std::cout << "No match found for " << std::hex << (int) opcode << "\n";
		std::exit(0);
	}
}

void Machine::update_timers(const std::chrono::steady_clock::time_point& now){
	auto time_span = std::chrono::duration_cast<std::chrono::duration<int,std::milli>>(now - last_tick);
	int to_reduce = time_span.count()/16;
	if(to_reduce > 0){
		last_tick = now - std::chrono::duration<int,std::milli>(time_span.count()%16);
	}
	DT = (DT >= to_reduce) ? (DT - to_reduce) : 0;
	ST = (ST >= to_reduce) ? (ST - to_reduce) : 0;

	// TODO - Update Sound state
}

void Machine::print_machine_state(){
	std::cout << "DT " << (int)DT << "\t" << "ST " << (int)ST << "\t" << "I " << (int) I << "\t" << "SP " << (int) SP << "\t" << "PC " << (int) PC<< "\n";
	for(int i = 0; i < 16; ++i){
		std::cout << "V" << std::hex << i << " " ; std::cout << (int)registers[i] << "  ";
	}
	std::cout << "\nStack: ";
	for(int i = 0; i < 64; ++i){
		std::cout << (int)stack[i] << " ";
	}
	/* std::cout << "\nMemory: ";
	for(int i = 0; i < 4096; ++i){
		std::cout << (int)memory[i] << " ";
		} */
	std::cout << "\n";
}

void Machine::runLoop(){
	while(true){
		// Update display
		if(ge.is_dirty()){
			ge.update_display();
			print_machine_state();
		}
		kb.update_pressed_keys();
		
		// Fetch Instruction and execute
		uint16_t opcode = (memory[PC]<<8) | (memory[PC+1]);
		PC += 2; // Increment Program Counter;
		execute(opcode);

		// Update timers
		auto time_now = std::chrono::steady_clock::now();
		// update_sound_timer(time_now);
		// update_delay_timer(time_now);
		update_timers(time_now);
		
		// std::this_thread::sleep_for(std::chrono::milliseconds(5));
		// std::cin.get();
	}
}
