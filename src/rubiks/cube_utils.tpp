#include "cube_utils.h"

namespace rubiks {

template <typename T>
void rotate_ninety_degrees(std::vector<T>& data, int width, int height, bool reverse) {
	auto convert = [=](int x, int y) {
		if (reverse) {
			return (height - y - 1) + x * height;
		} else {
			return (width - x - 1) * height + y;
		}
	};
	if (width != height) {
		std::swap(width, height);
	}
	std::vector<T> result(width * height);
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			const int index = y * width + x;
			const int rotated_index = convert(x, y);
			result[index] = std::move(data[rotated_index]);
		}
	}
	data = std::move(result);
}

}	// rubiks namespace
