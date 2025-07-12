#ifndef COLOR_H
#define COLOR_H

#include <stdexcept>

namespace rubiks {

enum class color {
	yellow,
	red,
	green,
	orange,
	blue,
	white
};

constexpr int to_int(color c) {
	return static_cast<int>(c);
}

constexpr char translate(color c) {
	constexpr char names[6] = {'y','r','g','o','b','w'};
	return names[to_int(c)];
}

inline color int_to_color(int i) {
	if (i < to_int(color::yellow) || to_int(color::white) < i) {
		throw std::out_of_range{"color value out of range"};
	}
	return color{i};
}

inline color& operator++(color& col) {
	col = (col != color::white) ? color{to_int(col) + 1} : color::yellow;
	return col;
}

inline color operator++(color& col, int) {
	color old = col;
	++col;
	return old;
}

inline color& operator--(color& col) {
	col = (col != color::yellow) ? color{to_int(col) - 1} : color::white;
	return col;
}

inline color operator--(color& col, int) {
	color old = col;
	--col;
	return old;
}

}	// rubiks namespace

#endif
