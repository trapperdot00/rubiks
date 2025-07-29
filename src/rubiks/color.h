#ifndef COLOR_H
#define COLOR_H

namespace rubiks {

enum class color {
	yellow,
	red,
	green,
	orange,
	blue,
	white
};

int to_int(color);
char translate(color);
color int_to_color(int);

color& operator++(color&);
color operator++(color&, int);
color& operator--(color&);
color operator--(color&, int);

}	// rubiks namespace

#endif
