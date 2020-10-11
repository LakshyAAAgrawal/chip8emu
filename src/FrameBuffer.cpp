#include <stdint.h>
#include "../include/FrameBuffer.hpp"
FrameBuffer::FrameBuffer(){
}

void FrameBuffer::cls(){
	fb.fill(std::array<uint8_t, 4>());
}
