#include "axis.h"

#include <stdexcept>
#include <cctype>

namespace rubiks {

axis to_axis(char ch) {
	switch (std::tolower(ch)) {
	case 'x':
		return axis::x;
	case 'y':
		return axis::y;
	case 'z':
		return axis::z;
	default:
		throw std::invalid_argument{"invalid axis"};
	}
}

axis to_axis(int i) {
	if (i < to_int(axis::x) || to_int(axis::z) < i) {
		throw std::out_of_range{"axis out of range"};
	}
	return axis{i};
}

int to_int(axis a) {
	return static_cast<int>(a);
}

char to_char(axis ax) {
	switch (ax) {
	case axis::x:
		return 'x';
	case axis::y:
		return 'y';
	case axis::z:
		return 'z';
	default:
		throw std::invalid_argument{"unknown axis"};
	}
}

}	// rubiks namespace
