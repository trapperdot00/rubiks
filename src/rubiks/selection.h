#ifndef SELECTION_H
#define SELECTION_H

#include "face.h"

namespace rubiks {

enum class direction {
	vertical,
	horizontal
};

struct selection {
	face side;
	direction dir;
};

constexpr bool is_column(selection s) {
	return s.dir == direction::vertical;
}

constexpr bool is_row(selection s) {
	return s.dir == direction::horizontal;
}

}	// rubiks namespace

#endif
