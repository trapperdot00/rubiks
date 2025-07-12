#include "cube_utils.h"

namespace rubiks {

template <typename T, size_t size>
void rotate_ninety_degrees(std::array<T, size>& arr, int width, int height, bool counterclockwise) {
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
	std::array<T, size> new_arr;
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int index = y * width + x;
			int rotated_index = convert(x, y);
			new_arr.at(index) = std::move(arr.at(rotated_index));
		}
	}
	arr = std::move(new_arr);
}

}	// rubiks namespace
