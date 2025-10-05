#include "../src/rubiks/game/cli_game.h"
#include "../src/rubiks/tile/colored_numbered_tile.h"

#include <string>

int main(int argc, char* argv[]) try {
	if (argc < 2) {
		throw std::runtime_error{"usage: <program> <cube_size>"};
	}
	size_t size = std::stoull(argv[1]);
	rubiks::cli_game<rubiks::colored_numbered_tile> game(size);
	game.play();
} catch (const std::exception& err) {
	std::cerr << "Error: " << err.what() << '\n';
}
