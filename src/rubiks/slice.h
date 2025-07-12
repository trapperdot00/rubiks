#ifndef SLICE_H
#define SLICE_H

#include <stdexcept>

namespace rubiks {

enum class slice {
	top_row,
	middle_row,
	bottom_row,
	left_column,
	middle_column,
	right_column
};

constexpr int to_int(slice s) {
	return static_cast<int>(s);
}

inline slice to_slice(int i) {
	if (i < to_int(slice::top_row) || to_int(slice::right_column) < i) {
		throw std::out_of_range{"slice out of range"};
	}
	return slice{i};
}

constexpr int operator-(slice lhs, slice rhs) {
	return to_int(lhs) - to_int(rhs);
}

constexpr bool is_horizontal(slice s) {
	return to_int(s) < to_int(slice::left_column);
}

constexpr bool is_vertical(slice s) {
	return !is_horizontal(s);
}

}	// rubiks namespace

#endif
