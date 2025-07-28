#ifndef CLI_GAME_H
#define CLI_GAME_H

#include "../cube.h"

#include <iostream>
#include <iomanip>
#include <cstddef>
#include <memory>
#include <random>
#include <chrono>

namespace rubiks {

template <typename tile_type = colored_tile>
class cli_game {
public:
	cli_game(size_t length) :
		cube_ptr{std::make_unique<cube<tile_type>>(length)}
	{}
	cli_game() : cli_game(3) {}
	void shuffle(size_t steps = 5);
	void play();
	bool solved() const { return cube_ptr->solved(); }
	cube<tile_type> get_cube() const { return *cube_ptr; }
private:
	std::ostream& print_cube(std::ostream&) const;

	std::unique_ptr<cube<tile_type>> cube_ptr;
};

#include "cli_game.tpp"

}	// rubiks namespace

#endif
