#include <stdint.h>
#include "../include/kbhit.hpp"
#include <vector>
#include <map>

class Keyboard{
private:
	keyboard kb;
	std::vector<int> pressed_keys;
	std::map<int, uint8_t> key_map;
public:
	Keyboard();
	void update_pressed_keys();
	bool isKeyDown(uint8_t key);
	uint8_t waitAndGetKeypress();
};
