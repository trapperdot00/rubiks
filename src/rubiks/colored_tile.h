#ifndef COLORED_TILE_H
#define COLORED_TILE_H

#include "tile_base.h"
#include "color.h"

#include <cstddef>
#include <string>

namespace rubiks {

// Defines a tile with a representation of a color
class colored_tile : virtual public tile_base {
public:
	colored_tile() = default;
	colored_tile(size_t face, size_t tile) :
		tile_base{face, tile},
		col{int_to_color(face)}
	{}
	std::string rep() const override {
		return std::string{translate(col)};
	}
	color get_color() const { return col; }
private:
	color col = color::white;
};

}	// rubiks namespace

#endif
