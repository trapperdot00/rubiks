#ifndef COLORED_TILE
#define COLORED_TILE

#include "tile_base.h"
#include "color.h"

namespace rubiks {

class colored_tile : virtual public tile_base {
public:
	colored_tile(int face, int tile) :
		tile_base{face, tile},
		col{int_to_color(face)}
	{}
	std::string rep() const override {
		return std::string{translate(col)};
	}
	color get_color() const { return col; }
private:
	color col;
};

}	// rubiks namespace

#endif
