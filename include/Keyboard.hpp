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
	bool update_pressed_keys(); // Returns true if there is an interrupt
	bool isKeyDown(uint8_t key);
	uint8_t waitAndGetKeypress();
};
