#ifndef COLOR_H
#define COLOR_H

namespace rubiks {

// Defines the possible colors of the tiles of a cube
enum class color {
	yellow,
	red,
	green,
	orange,
	blue,
	white
};

// Converts a color to an integer
int to_int(color);

// Converts a color to a human-readable character
char translate(color);

// Converts an integer to a color
color int_to_color(int);

// Get the next or previous color,
// wrapping around on under- and overflow
color& operator++(color&);
color operator++(color&, int);
color& operator--(color&);
color operator--(color&, int);

}	// rubiks namespace

#endif
