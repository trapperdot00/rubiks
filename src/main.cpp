#include "rubiks/cube_3x3.h"
#include "rubiks/colored_numbered_tile.h"

#include <map>

void game() {
	using namespace rubiks;
	static const std::map<char, cube_3x3<colored_numbered_tile>& (cube_3x3<colored_numbered_tile>::*)(bool)> f {
		{'u', &cube_3x3<colored_numbered_tile>::turn_up},
		{'d', &cube_3x3<colored_numbered_tile>::turn_down},
		{'r', &cube_3x3<colored_numbered_tile>::turn_right},
//		{'l', &cube_3x3<colored_numbered_tile>::turn_left},
//		{'f', &cube_3x3<colored_numbered_tile>::turn_front},
//		{'b', &cube_3x3<colored_numbered_tile>::turn_back},
	};
	cube_3x3<colored_numbered_tile> cube;
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

int main() {
	game();
}
