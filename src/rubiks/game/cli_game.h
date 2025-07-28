#ifndef CLI_GAME_H
#define CLI_GAME_H

#include "../cube.h"

namespace rubiks {

template <typename tile_type>
class cli_game {
public:
	cube<tile_type> get_cube() const { return cube_; }
private:
	cube<tile_type> cube_;
};

}	// rubiks namespace

#endif
