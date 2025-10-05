#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "layer.h"

namespace rubiks {

// Specifies a movement by a source
// and a destination layer
struct movement {
	layer from;
	layer to;
};

// Returns whether the tiles should
// be reversed during the movement
bool reversed(movement);

}	// rubiks namespace

#endif
