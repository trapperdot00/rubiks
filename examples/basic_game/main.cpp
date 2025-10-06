#include "cli_game.h"
#include "colored_numbered_tile.h"

#include <stdexcept>
#include <string>
#include <iostream>

/*	Example usage of cli_game
 *
 *	This program constructs a cli_game object with the cube length
 *	passed in as a command-line argument.
 *	
 *	The tile objects are of type colored_numbered_tile, each tile
 *	shows up as a color (abbreviated as a single character),
 *	and a number unique to that color.
 *	
 *	The cube is first shuffled using 25 randomized moves.
 *
 *	The game is then started using the play method of cli_game,
 *	and takes in moves from the console using the axis-offset notation.
 *
 *	Moves are asked from the user until the cube is solved.
 */

int main(int argc, char* argv[]) try {
	if (argc < 2) {
		throw std::runtime_error{"usage: <program> <cube_size>"};
	}

	size_t size = std::stoull(argv[1]);
	constexpr size_t shuffle_steps = 25;

	rubiks::cli_game<rubiks::colored_numbered_tile> game(size);
	std::cout << "Constructed " << size << 'x' << size << 'x' << size << " Rubik's cube.\n\n";

	game.shuffle(shuffle_steps);
	std::cout << "Shuffled using " << shuffle_steps << " moves.\n\n";

	std::cout << "Ready to play.\n\n";
	game.play();

} catch (const std::exception& err) {
	std::cerr << err.what() << '\n';
}
