#include "../include/GraphicEngine.hpp"
#include <algorithm>
#include <iostream>
#include <string>

// From https://stackoverflow.com/questions/17335816/clear-screen-using-c
void ClearScreen(){
	std::cout << "\033[2J\033[1;1H";
}

GraphicEngine::GraphicEngine(){
	cls();
}

void GraphicEngine::cls(){
	// TODO
	fb.fill(std::bitset<64>(0));
	dirty = true;
}

uint8_t GraphicEngine::draw_sprite(std::vector<uint8_t>::iterator start, std::vector<uint8_t>::iterator end, uint8_t x, uint8_t y){
	bool b = false;
	for(uint8_t curr_y = y; curr_y <= 0x1f && start != end; ++start, ++curr_y){
		std::bitset<64> sprite_y(*start);
		std::bitset<64> org = fb[curr_y];

		// Uncomment the following line to wrap the sprite around the screen instead of clipping it
		// sprite_y = (x <= 56) ? (sprite_y << (56 - x)) : ((sprite_y >> (x - 56)) | (sprite_y << (120-x)));
		sprite_y = (x <= 56) ? (sprite_y << (56 - x)) : (sprite_y >> (x - 56));
		fb[curr_y] = fb[curr_y] ^ sprite_y;

		// Update display related flags
		if((org & (~fb[curr_y])).count() > 0) b = true;
		if((org ^ fb[curr_y]).count() > 0) dirty = true;
	}
	
	return b?1:0;
}

std::string GraphicEngine::screen_as_string(){
	std::string s;
	s.append("╔");
	for(int i = 0; i < 64; ++i){
		s.append("═");
	}
	s.append("╗");
	s.push_back('\n');
	for(int i = 0; i < 16; ++i){
		s.append("║");
		for(int j = 63; j >= 0; --j){ // bitset indexes are right-to-left
			if(fb[2*i].test(j)){
				if(fb[2*i + 1].test(j)){
					s.append("█");
				}else{
					s.append("▀");
				}
			}else{
				if(fb[2*i + 1].test(j)){
					s.append("▄");
				}else{
					s.append(" ");
				}
			}
		}
		s.append("║\n");
	}
	s.append("╚");
	for(int i = 0; i < 64; ++i){
		s.append("═");
	}
	s.append("╝\n");
	return s;
}

void GraphicEngine::update_display(){
	ClearScreen();
	std::cout << screen_as_string();
	dirty = false;
}

bool GraphicEngine::is_dirty(){
	return dirty;
}
