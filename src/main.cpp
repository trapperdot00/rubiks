#include "rubiks/cube.h"
#include "rubiks/colored_numbered_tile.h"

#include <map>

template <size_t length>
void game() {
	using namespace rubiks;
	static const std::map<char, cube<length, colored_numbered_tile>& (cube<length, colored_numbered_tile>::*)(bool)> f {
		{'u', &cube<length, colored_numbered_tile>::turn_up},
		{'d', &cube<length, colored_numbered_tile>::turn_down},
		{'r', &cube<length, colored_numbered_tile>::turn_right},
		{'l', &cube<length, colored_numbered_tile>::turn_left},
		{'f', &cube<length, colored_numbered_tile>::turn_front},
		{'b', &cube<length, colored_numbered_tile>::turn_back},
	};
	cube<length, colored_numbered_tile> cube;
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
	game<3>();
}
