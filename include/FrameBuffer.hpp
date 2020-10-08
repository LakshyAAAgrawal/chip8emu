#include <stdint.h>
#include <array>

using namespace std;
class FrameBuffer{
private:
	array<array<uint8_t, 4> ,64> fb;
public:
	FrameBuffer();
};
