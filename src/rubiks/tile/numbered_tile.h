#ifndef NUMBERED_TILE_H
#define NUMBERED_TILE_H

#include "tile_base.h"

namespace rubiks {

// Defines a tile with a representation
// of a number unique to a given side
class numbered_tile : virtual public tile_base {
public:
	numbered_tile() = default;
	numbered_tile(size_t face, size_t tile) :
		tile_base{face, tile}
	{}
	std::string rep() const override {
		return std::to_string(get_number());
	}
	virtual int get_number() const { return tile_num(); }
};

}	// rubiks namespace

#endif
