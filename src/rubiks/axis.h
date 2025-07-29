#ifndef AXIS_H
#define AXIS_H

namespace rubiks {

enum class axis {
	x, y, z
};

// Converts an integer to an axis
axis to_axis(int);

// Converts a human-readable character to an axis
axis to_axis(char);

// Converts an axis to an integer
int to_int(axis);

// Converts an axis to a human-readable character
char to_char(axis);

}	// rubiks namespace

#endif
