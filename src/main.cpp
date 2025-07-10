#include "rubiks/cube_3x3.h"
#include "rubiks/colored_numbered_tile.h"

int main() {
	rubiks::cube_3x3<rubiks::colored_numbered_tile> cube;
	std::cout << "initial state:\n" << cube << '\n';

	cube.turn_up();
	std::cout << "U from initial:\n" << cube << '\n';
}
