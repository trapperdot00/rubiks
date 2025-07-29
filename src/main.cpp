#include "rubiks/game/cli_game.h"
#include "rubiks/colored_numbered_tile.h"

int main() {
	size_t size = 0;
	std::cout << "Enter cube length: ";
	if (!(std::cin >> size)) {
		throw std::runtime_error{"no input"};
	}
	rubiks::cli_game<rubiks::colored_tile> game(size);
	game.play();
}
