#include <stdint.h>
#include <array>

class FrameBuffer{
private:
	std::array<std::array<uint8_t, 4> ,64> fb;
public:
	FrameBuffer();
	void cls();
};
