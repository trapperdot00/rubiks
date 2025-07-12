#ifndef COLORED_NUMBERED_TILE_H
#define COLORED_NUMBERED_TILE_H

#include "colored_tile.h"
#include "numbered_tile.h"

namespace rubiks {

class colored_numbered_tile : public colored_tile, public numbered_tile {
public:
	colored_numbered_tile() = default;
	colored_numbered_tile(int face, int tile) :
		tile_base{face, tile},
		colored_tile{face, tile},
		numbered_tile{face, tile}
	{}
	std::string rep() const override {
		return colored_tile::rep() + numbered_tile::rep();
	}
};

}	// rubiks namespace

#endif
