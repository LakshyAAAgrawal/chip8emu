#include <stdint.h>
#include "../include/kbhit.hpp"

class Keyboard{
private:
	keyboard kb;
public:
	bool isKeyDown(uint8_t key);
	uint8_t waitAndGetKeypress();
};
