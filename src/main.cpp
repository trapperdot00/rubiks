#include "rubiks/game/cli_game.h"
#include "rubiks/colored_numbered_tile.h"

#include <string>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		throw std::runtime_error{"usage: <program> <cube_size>"};
	}
	size_t size = std::stoull(argv[1]);
	rubiks::cli_game<rubiks::colored_numbered_tile> game(size);
	game.play();
}
