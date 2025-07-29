#ifndef SELECTION_H
#define SELECTION_H

#include "face.h"
#include "direction.h"

namespace rubiks {

struct selection {
	face side;
	direction dir;
};

bool is_column(selection);
bool is_row(selection);

}	// rubiks namespace

#endif
