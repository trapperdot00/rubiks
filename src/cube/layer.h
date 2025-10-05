#ifndef LAYER_H
#define LAYER_H

#include "selection.h"

#include <cstddef>

namespace rubiks {

// Fully specifies a selected layer on a cube
struct layer {
	selection sel;	// Side and direction
	size_t offset;	// in columns: offset from left
					// in rows: offset from top
};

}	// rubiks namespace

#endif
