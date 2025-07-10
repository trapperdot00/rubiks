#ifndef CUBE_BASE_H
#define CUBE_BASE_H

#include "tile_base.h"

#include <vector>
#include <memory>
#include <stdexcept>
#include <iterator>
#include <utility>

namespace rubiks {

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

template <typename It>
void rotate_face(It first, It last, int width, int height) {
	if (width * height != std::distance(first, last)) {
		throw std::range_error{"face's size not equal to given iterator range's size"};
	}
	std::vector<std::shared_ptr<tile_base>> temp;
	temp.reserve(width * height);
	for (int col = 0; col < width; ++col) {
		int offset = width * (height - 1) + col;
		for (int row = 0; row < height; ++row) {
			It it = first;
			std::advance(it, offset);
			temp.push_back(std::move(*it));
			offset -= width;
		}
	}
	for (int i = 0; i < width * height; ++i) {
		*first++ = std::move(temp[i]);
	}
}

class cube_base {
public:
	cube_base(int face_count, int tile_per_face) :
		face_no{face_count},
		tpf{tile_per_face}
	{}
	int face_num() const { return face_no; }
	int tiles_per_face() const { return tpf; }
	int tile_num() const {
		return face_num() * tiles_per_face();
	}

	virtual int width() const = 0;
	virtual int height() const = 0;
	virtual std::shared_ptr<tile_base> operator[](int) const = 0;
	virtual ~cube_base() = default;
private:
	int face_no;
	int tpf;
};

}	// rubiks namespace

#endif
