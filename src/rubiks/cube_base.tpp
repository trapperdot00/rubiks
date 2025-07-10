#ifndef CUBE_BASE_TPP
#define CUBE_BASE_TPP

#include <deque>

namespace rubiks {

template <typename It>
void rotate_face(It first, It last, int width, int height, bool reverse) {
	if (width * height != std::distance(first, last)) {
		throw std::range_error{"face's size not equal to given iterator range's size"};
	}
	std::deque<std::shared_ptr<tile_base>> temp;
	for (int col = 0; col < width; ++col) {
		int offset = width * (height - 1) + col;
		for (int row = 0; row < height; ++row) {
			It it = first;
			std::advance(it, offset);
			if (reverse) {
				temp.push_front(std::move(*it));
			} else {
				temp.push_back(std::move(*it));
			}
			offset -= width;
		}
	}
	for (int i = 0; i < width * height; ++i) {
		*first++ = std::move(temp[i]);
	}
}

template <typename tile_type>
std::vector<std::shared_ptr<tile_base>>
init_tile_data(int face_num, int tiles_per_face) {
	std::vector<std::shared_ptr<tile_base>> ret;
	for (int face = 0; face < face_num; ++face) {
		for (int tile = 0; tile < tiles_per_face; ++tile) {
			ret.push_back(std::make_shared<tile_type>(face, tile));
		}
	}
	return ret;
}

}	// rubiks namespace

#endif
