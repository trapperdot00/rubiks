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
	rotate_face(face::up, prime);
	return *this;
}

template <typename tile_type>
std::weak_ptr<tile_base> cube_3x3<tile_type>::get_tile(face f, int row, int col) const {
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
std::array<std::shared_ptr<tile_base>, 3> cube_3x3<tile_type>::get_row(face f, int row) const {
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
std::array<std::shared_ptr<tile_base>, 3> cube_3x3<tile_type>::get_col(face f, int col) const {
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
				os << cube.get_tile(to_face(face), row, col).lock()->rep() << ' ';
			}
		}
		os << '\n';
	}
	return os;
}

template <typename tile_type>
void cube_3x3<tile_type>::rotate_face(face f, bool prime) {
	auto convert = [prime](int x, int y) {
		if (prime) {
			return x * height + (height - y - 1);
		} else {
			return (width - x - 1) * height + y;
		}
	};
	std::array<std::shared_ptr<tile_base>, tiles_per_face> temp;
	auto& side = tile_data.at(to_int(f));
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int index = y * width + x;
			int rotated_index = convert(x, y);
			std::cout << "x: " << x << " y: " << y << " i: " << index << " r: " << rotated_index << '\n';
			temp.at(index) = side.at(rotated_index);
		}
	}
	std::cout << "--------------\n";
	for (const auto& p : temp) {
		std::cout << p->rep() << ' ';
	}
	std::cout << "\n--------------\n";
	side = std::move(temp);
}

}	// rubiks namespace

#endif
