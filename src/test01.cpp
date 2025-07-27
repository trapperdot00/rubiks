#include "rubiks/static_numbered_tile.h"
#include "rubiks/cube.h"

#include <string>
#include <iostream>

rubiks::axis char_to_axis(char ch) {
	rubiks::axis axis;
	switch (ch) {
	case 'x':
		axis = rubiks::axis::x;
		break;
	case 'y':
		axis = rubiks::axis::y;
		break;
	case 'z':
		axis = rubiks::axis::z;
		break;
	default:
		throw std::runtime_error{"invalid axis"};
	}
	return axis;
}

int main() {
	size_t length = 0;
	std::cout << "enter cube length: ";
	if (!(std::cin >> length)) {
		throw std::runtime_error{"invalid length"};
	}
	rubiks::cube<rubiks::static_numbered_tile> cube(length);
	std::cout << "enter axis and offset:\n";
	while (true) {
		char ch = 0;
		if (!(std::cin >> ch)) {
			break;
		}
		rubiks::axis axis = char_to_axis(ch);
		size_t offset = 0;
		if (!(std::cin >> offset)) {
			throw std::runtime_error{"invalid offset"};
		}
		cube.turn(axis, offset);
		std::cout << std::string(50, '-') << '\n';
		std::cout << cube << '\n';
		std::cout << "enter axis and offset:\n";
	}
}
