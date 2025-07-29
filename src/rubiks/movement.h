#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "layer.h"

namespace rubiks {

struct movement {
	layer from;
	layer to;
};

bool reversed(movement);

}	// rubiks namespace

#endif
