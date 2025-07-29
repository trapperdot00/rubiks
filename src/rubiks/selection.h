#ifndef SELECTION_H
#define SELECTION_H

#include "face.h"
#include "direction.h"

namespace rubiks {

// Specifies which side and which direction
// a selection is on
struct selection {
	face side;
	direction dir;
};

// Compares the direction of a selection
bool is_column(selection);
bool is_row(selection);

}	// rubiks namespace

#endif
