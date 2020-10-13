#include <stdint.h>
#include <vector>
#include <array>
#include <bitset>
#include <string>

class GraphicEngine{
private:
	std::array<std::bitset<64>, 32> fb;
	std::string screen_as_string();
	bool dirty;
public:
	GraphicEngine();
	void cls();
	uint8_t draw_sprite(std::vector<uint8_t>::iterator start, std::vector<uint8_t>::iterator end, uint8_t x, uint8_t y);
	void update_display();
	bool is_dirty();
};
