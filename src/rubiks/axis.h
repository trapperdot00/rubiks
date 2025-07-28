#ifndef AXIS_H
#define AXIS_H

namespace rubiks {

enum class axis {
	x, y, z
};

axis to_axis(int);
axis to_axis(char);
int to_int(axis);
char to_char(axis);

}	// rubiks namespace

#endif
