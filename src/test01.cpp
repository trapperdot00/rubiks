#include "rubiks/static_numbered_tile.h"
#include "rubiks/colored_numbered_tile.h"
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
	rubiks::cube<rubiks::colored_numbered_tile> cube(length);
	constexpr size_t n = 80;
	std::cout << std::string(n, '#') << '\n';
	std::cout << "enter turn-axis and offset: ";
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
		std::cout << std::string(n, '-') << '\n';
		cube.turn(axis, offset);
		std::cout << std::string(n, '-') << '\n';
		std::cout << cube << '\n';
		std::cout << std::string(n, '#') << '\n';
		std::cout << "enter turn-axis and offset: ";
	}
}
