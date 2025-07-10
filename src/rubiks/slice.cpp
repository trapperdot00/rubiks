#include "slice.h"

#include <stdexcept>

namespace rubiks {

int to_int(slice s) {
	return static_cast<int>(s);
}

slice to_slice(int i) {
	if (i < to_int(slice::top_row) || to_int(slice::right_column) < i) {
		throw std::out_of_range{"slice out of range"};
	}
	return slice{i};
}

int operator-(slice lhs, slice rhs) {
	return to_int(lhs) - to_int(rhs);
}

bool is_horizontal(slice s) {
	return to_int(s) < to_int(slice::left_column);
}

bool is_vertical(slice s) {
	return !is_horizontal(s);
}

}	// rubiks namespace
