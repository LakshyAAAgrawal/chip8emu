#include <stdint.h>

class Keyboard{
private:
public:
	bool isKeyDown(uint8_t key);
	uint8_t waitAndGetKeypress();
};
