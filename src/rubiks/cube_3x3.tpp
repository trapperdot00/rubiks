#ifndef CUBE_3X3_TPP
#define CUBE_3X3_TPP

namespace rubiks {

template <typename tile_type>
void cube_3x3<tile_type>::reset() {
	for (int face = 0; face < 6; ++face) {
		for (int tile = 0; tile < 9; ++tile) {
			tile_data[face][tile] = std::make_shared<tile_type>(face, tile);
		}
	}
}

template <typename tile_type>
cube_3x3<tile_type>& cube_3x3<tile_type>::turn_up(bool prime) {
	rotate_ninety_degrees(get_face(face::up), width, height, prime);
	return *this;
}

template <typename tile_type>
std::shared_ptr<tile_base> cube_3x3<tile_type>::get_tile(face f, int row, int col) const {
	if (row >= height || row < 0) {
		throw std::out_of_range{"row out of range"};
	}
	if (col >= width || col < 0) {
		throw std::out_of_range{"col out of range"};
	}
	const int tile = row * width + col;
	return tile_data.at(to_int(f)).at(tile);
}

template <typename tile_type>
std::array<std::shared_ptr<tile_base>, cube_3x3<tile_type>::width>
cube_3x3<tile_type>::get_row(face f, int row) {
	if (row >= height || row < 0) {
		throw std::out_of_range{"row out of range"};
	}
	std::array<std::shared_ptr<tile_base>, 3> ret;
	const auto& side = tile_data.at(to_int(f));
	for (int i = row * width; i < (row + 1) * width; ++i) {
		ret.at(i) = side.at(i);
	}
	return ret;
}

template <typename tile_type>
std::array<std::shared_ptr<tile_base>, cube_3x3<tile_type>::height>
cube_3x3<tile_type>::get_col(face f, int col) {
	if (col >= width || col < 0) {
		throw std::out_of_range{"col out of range"};
	}
	std::array<std::shared_ptr<tile_base>, 3> ret;
	const auto& side = tile_data.at(to_int(f));
	for (int i = col; i < height * width; i += width) {
		ret.at(i) = side.at(i);
	}
	return ret;
}

template <typename tile_type>
std::ostream& operator<<(std::ostream& os, const cube_3x3<tile_type>& cube) {
	for (int face = 0; face < cube.face_count; ++face) {
		for (int row = 0; row < cube.height; ++row) {
			for (int col = 0; col < cube.width; ++col) {
				os << cube.get_tile(to_face(face), row, col)->rep() << ' ';
			}
		}
		os << '\n';
	}
	return os;
}

}	// rubiks namespace

#endif
