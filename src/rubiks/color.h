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

color& operator++(color&);
color operator++(color&, int);
color& operator--(color&);
color operator--(color&, int);

color int_to_color(int);
int to_int(const color&);
char translate(const color&);

}	// rubiks namespace

#endif
