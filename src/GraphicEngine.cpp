#include "../include/GraphicEngine.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <ncurses.h>

// From https://stackoverflow.com/questions/17335816/clear-screen-using-c
void ClearScreen(){
	std::cout << "\033[2J\033[1;1H";
}

GraphicEngine::GraphicEngine(){
	//initscr();
	fb.fill(std::bitset<64>(0));
}

void GraphicEngine::cls(){
	// TODO
	fb.fill(std::bitset<64>(0));
}

uint8_t GraphicEngine::draw_sprite(std::vector<uint8_t>::iterator start, std::vector<uint8_t>::iterator end, uint8_t x, uint8_t y){
	bool b = false;
	for(uint8_t curr_y = y; curr_y <= 0x1f && start != end; ++start, ++curr_y){
		std::bitset<64> sprite_y(*start);
		std::bitset<64> org = fb[curr_y];
		// sprite_y = (x <= 56) ? (sprite_y << (56 - x)) : ((sprite_y >> (x - 56)) | (sprite_y << (120-x)));
		sprite_y = (x <= 56) ? (sprite_y << (56 - x)) : (sprite_y >> (x - 56));
		fb[curr_y] ^= sprite_y;
		for(int i = 0; x+i <= 0x3f && i < 8; ++i){
			if(org[(x+i)%64] && !fb[curr_y][(x+i)%64]) b = true;
		}
	}
	return b?1:0;
}

std::string GraphicEngine::screen_as_string(){
	std::string s;
	s.reserve(67*34);
	s.append(std::string(66, '#'));
	s.push_back('\n');
	for(auto& y: fb){
		s.push_back('#');
		for(char c: y.to_string()){
			if(c == '1') s.append("█");
			else s.append(" ");
		} 
		s.append("#\n");
	}
	s.append(std::string(66, '#'));
	s.push_back('\n');
	//std::replace(s.begin(), s.end(), '0', ' ');
	//std::replace(s.begin(), s.end(), '1', 'ș');
	return s;
}

void GraphicEngine::update_display(){
	ClearScreen();
	std::cout << screen_as_string();
}
