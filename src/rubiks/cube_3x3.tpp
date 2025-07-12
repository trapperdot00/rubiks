#ifndef CUBE_3X3_TPP
#define CUBE_3X3_TPP

namespace rubiks {

template <typename tile_type>
void cube_3x3<tile_type>::reset() {
	for (int face = 0; face < 6; ++face) {
		for (int tile = 0; tile < 9; ++tile) {
			tile_data[face][tile] = tile_type{face, tile};
		}
	}
}

template <typename tile_type>
cube_3x3<tile_type>& cube_3x3<tile_type>::turn_up(bool prime) {
	rotate_ninety_degrees(get_face(face::up), width, height, prime);
	return *this;
}

template <typename tile_type>
const tile_type& cube_3x3<tile_type>::get_tile(face f, int row, int col) const {
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
tile_type& cube_3x3<tile_type>::get_tile(face f, int row, int col) {
	return const_cast<tile_type&>(const_cast<const cube_3x3*>(this)->get_tile());
}

template <typename tile_type>
std::array<tile_type, cube_3x3<tile_type>::width>
cube_3x3<tile_type>::get_row(face f, int row) {
	if (row >= height || row < 0) {
		throw std::out_of_range{"row out of range"};
	}
	std::array<tile_type, width> ret;
	const auto& side = tile_data.at(to_int(f));
	for (int i = 0; i < width; ++i) {
		ret.at(i) = side.at(row * width + 1);
	}
	return ret;
}

template <typename tile_type>
std::array<tile_type, cube_3x3<tile_type>::height>
cube_3x3<tile_type>::get_col(face f, int col) {
	if (col >= width || col < 0) {
		throw std::out_of_range{"col out of range"};
	}
	std::array<tile_type, height> ret;
	const auto& side = tile_data.at(to_int(f));
	for (int i = 0; i < height; ++i) {
		ret.at(i) = side.at(i * width + col);
	}
	return ret;
}

template <typename tile_type>
const std::array<tile_type, cube_3x3<tile_type>::tiles_per_face>&
cube_3x3<tile_type>::get_face(face f) const {
	return tile_data.at(to_int(f));
}

template <typename tile_type>
std::array<tile_type, cube_3x3<tile_type>::tiles_per_face>&
cube_3x3<tile_type>::get_face(face f) {
	return tile_data.at(to_int(f));
}

template <typename tile_type>
std::ostream& operator<<(std::ostream& os, const cube_3x3<tile_type>& cube) {
	for (int face = 0; face < cube.face_count; ++face) {
		for (int row = 0; row < cube.height; ++row) {
			for (int col = 0; col < cube.width; ++col) {
				os << cube.get_tile(to_face(face), row, col).rep() << ' ';
			}
		}
		os << '\n';
	}
	return os;
}

}	// rubiks namespace

#endif
