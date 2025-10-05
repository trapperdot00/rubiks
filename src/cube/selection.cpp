#include "selection.h"

namespace rubiks {

bool is_column(selection s) {
	return s.dir == direction::vertical;
}

bool is_row(selection s) {
	return s.dir == direction::horizontal;
}

}	// rubiks namespace
