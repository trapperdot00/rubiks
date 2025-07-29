#ifndef CLI_GAME_H
#define CLI_GAME_H

#include "../cube.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstddef>
#include <memory>
#include <random>
#include <chrono>
#include <tuple>
#include <cctype>

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

std::tuple<axis, size_t, bool> parse_rotation(std::istream&);
axis parse_axis(std::istream&);
size_t parse_offset(std::istream&);
bool parse_prime(std::istream&);

#include "cli_game.tpp"

}	// rubiks namespace

#endif
