#ifndef STATIC_NUMBERED_TILE_H
#define STATIC_NUMBERED_TILE_H

#include "numbered_tile.h"

namespace rubiks {

// Defines a tile with a representation
// of a number unique to the whole program
class static_numbered_tile : virtual public numbered_tile {
public:
	static_numbered_tile() = default;
	static_numbered_tile(size_t face, size_t tile) :
		numbered_tile{face, tile},
		num{counter++}
	{}
	int get_number() const override {
		return num;
	}
private:
	int num;
	inline static int counter = 0;
};

}	// rubiks namespace

#endif
