#include "cube_utils.h"

namespace rubiks {

template <typename T>
void rotate_ninety_degrees(std::vector<T>& vec, int width, int height, bool counterclockwise) {
	auto convert = [&](int x, int y) {
		if (counterclockwise) {
			return (height - y - 1) + x * height;
		} else {
			return (width - x - 1) * height + y;
		}
	};
	if (width != height) {
		std::swap(width, height);
	}
	std::vector<T> new_vec(vec.size());
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int index = y * width + x;
			int rotated_index = convert(x, y);
			new_vec.at(index) = std::move(vec.at(rotated_index));
		}
	}
	vec = std::move(new_vec);
}

}	// rubiks namespace
