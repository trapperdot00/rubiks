#include "color.h"

#include <stdexcept>

namespace rubiks {

color& operator++(color& col) {
	col = (col != color::white) ? color{to_int(col) + 1} : color::yellow;
	return col;
}

color operator++(color& col, int) {
	color old = col;
	++col;
	return old;
}

color& operator--(color& col) {
	col = (col != color::yellow) ? color{to_int(col) - 1} : color::white;
	return col;
}

color operator--(color& col, int) {
	color old = col;
	--col;
	return old;
}

color int_to_color(int i) {
	if (i < to_int(color::yellow) || to_int(color::white) < i) {
		throw std::out_of_range{"color value out of range"};
	}
	return color{i};
}

int to_int(const color& col) {
	return static_cast<int>(col);
}

char translate(const color& col) {
	static constexpr int size = 6;
	static constexpr char names[size] = {
		'y', 'r', 'g', 'o', 'b', 'w'
	};
	return names[to_int(col)];
}

}	// rubiks namespace
