#include "rubiks/cube.h"
#include "rubiks/colored_numbered_tile.h"

#include <map>

template <size_t length, typename tile_type>
void game() {
	using namespace rubiks;
	static const std::map<char, cube<length, tile_type>& (cube<length, tile_type>::*)(bool)> f {
		{'u', &cube<length, tile_type>::turn_up},
		{'d', &cube<length, tile_type>::turn_down},
		{'r', &cube<length, tile_type>::turn_right},
		{'l', &cube<length, tile_type>::turn_left},
		{'f', &cube<length, tile_type>::turn_front},
		{'b', &cube<length, tile_type>::turn_back},
	};
	cube<length, tile_type> cube;
	std::cout << cube << '\n';
	std::cout << "enter movement: ";
	for (std::string cmd; std::cin >> cmd; ) {
		if (cmd.empty()) {
			continue;
		}
		if (auto it = f.find(std::tolower(cmd[0])); it != f.cend()) {
			bool prime = (cmd.size() > 1 && cmd[1] == '\'');
			(cube.*it->second)(prime);
		} else {
			std::cout << "invalid command: " << cmd << '\n';
		}
		std::cout << cube << '\n';
		std::cout << "enter movement: ";
	}
}

#ifndef SIZE
#error SIZE NOT GIVEN
#endif

#ifndef TILE
#error TILE NOT GIVEN
#endif

int main() {
	game<SIZE, TILE>();
}
