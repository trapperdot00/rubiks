#include "rubiks/cube_3x3.h"
#include "rubiks/colored_numbered_tile.h"

int main() {
	rubiks::cube_3x3<rubiks::colored_numbered_tile> cube;
	std::cout << "initial state:\n" << cube << '\n';

	for (int i = 0; i < 4; ++i) {
		cube.turn_down();
		std::cout << "D turn no. " << i + 1 << '\n' << cube << '\n';
	}
}
