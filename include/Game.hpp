#include "../include/Machine.hpp"
#include <stdint.h>

class Game{
private:
	Machine machine();
public:
	Game();
	void runLoop();
	void loadInstructions(uint8_t *);
};
