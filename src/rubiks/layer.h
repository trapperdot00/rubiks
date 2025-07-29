#ifndef LAYER_H
#define LAYER_H

#include "selection.h"

#include <cstddef>

namespace rubiks {

struct layer {
	selection sel;
	size_t offset;	// in columns: offset from left
					// in rows: offset from top
};

}	// rubiks namespace

#endif
