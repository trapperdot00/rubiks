#ifndef SLICE_H
#define SLICE_H

namespace rubiks {

enum class slice {
	top_row,
	middle_row,
	bottom_row,
	left_column,
	middle_column,
	right_column
};

int to_int(slice);
slice int_to_slice(int);
int operator-(slice, slice);
bool is_horizontal(slice);
bool is_vertical(slice);

}	// rubiks namespace

#endif
