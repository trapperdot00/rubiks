#ifndef CUBE_TPP
#define CUBE_TPP

namespace rubiks {

template <size_t length, typename tile_type>
void cube<length, tile_type>::reset() {
	for (size_t face = 0; face < face_count; ++face) {
		for (size_t tile = 0; tile < tiles_per_face; ++tile) {
			tile_data[face][tile] = tile_type{face, tile};
		}
	}
}

template <size_t length, typename tile_type>
void cube<length, tile_type>::turn(axis ax, size_t offset, bool prime) {
	// TODO
}

template <size_t length, typename tile_type>
cube<length, tile_type>& cube<length, tile_type>::turn_up(bool prime) {
	rotate_face(face::up, prime);
	if (!prime) {
		static const std::array<movement, 4> moves {{
			{{face::front, direction::horizontal, 0}, {face::left, direction::horizontal, 0}},
			{{face::left, direction::horizontal, 0}, {face::back, direction::horizontal, 0}},
			{{face::back, direction::horizontal, 0}, {face::right, direction::horizontal, 0}},
			{{face::right, direction::horizontal, 0}, {face::front, direction::horizontal, 0}}
		}};
		move(moves);
	} else {
		static const std::array<movement, 4> moves {{
			{{face::front, direction::horizontal, 0}, {face::right, direction::horizontal, 0}},
			{{face::right, direction::horizontal, 0}, {face::back, direction::horizontal, 0}},
			{{face::back, direction::horizontal, 0}, {face::left, direction::horizontal, 0}},
			{{face::left, direction::horizontal, 0}, {face::front, direction::horizontal, 0}}
		}};
		move(moves);
	}
	return *this;
}

template <size_t length, typename tile_type>
cube<length, tile_type>& cube<length, tile_type>::turn_down(bool prime) {
	rotate_face(face::down, prime);
	if (!prime) {
		static const std::array<movement, 4> moves {{
			{{face::front, direction::horizontal, length - 1}, {face::right, direction::horizontal, length - 1}},
			{{face::right, direction::horizontal, length - 1}, {face::back, direction::horizontal, length - 1}},
			{{face::back, direction::horizontal, length - 1}, {face::left, direction::horizontal, length - 1}},
			{{face::left, direction::horizontal, length - 1}, {face::front, direction::horizontal, length - 1}}
		}};
		move(moves);
	} else {
		static const std::array<movement, 4> moves {{
			{{face::front, direction::horizontal, length - 1}, {face::left, direction::horizontal, length - 1}},
			{{face::left, direction::horizontal, length - 1}, {face::back, direction::horizontal, length - 1}},
			{{face::back, direction::horizontal, length - 1}, {face::right, direction::horizontal, length - 1}},
			{{face::right, direction::horizontal, length - 1}, {face::front, direction::horizontal, length - 1}}
		}};
		move(moves);
	}
	return *this;
}

template <size_t length, typename tile_type>
cube<length, tile_type>& cube<length, tile_type>::turn_right(bool prime) {
	rotate_face(face::right, prime);
	if (!prime) {
		static const std::array<movement, 4> moves {{
			{{face::front, direction::vertical, length - 1}, {face::up, direction::vertical, length - 1}},
			{{face::up, direction::vertical, length - 1}, {face::back, direction::vertical, 0}},
			{{face::back, direction::vertical, 0}, {face::down, direction::vertical, length - 1}},
			{{face::down, direction::vertical, length - 1}, {face::front, direction::vertical, length - 1}}
		}};
		move(moves);
	} else {
		static const std::array<movement, 4> moves {{
			{{face::front, direction::vertical, length - 1}, {face::down, direction::vertical, length - 1}},
			{{face::down, direction::vertical, length - 1}, {face::back, direction::vertical, 0}},
			{{face::back, direction::vertical, 0}, {face::up, direction::vertical, length - 1}},
			{{face::up, direction::vertical, length - 1}, {face::front, direction::vertical, length - 1}}
		}};
		move(moves);
	}
	return *this;
}

template <size_t length, typename tile_type>
cube<length, tile_type>& cube<length, tile_type>::turn_left(bool prime) {
	rotate_face(face::left, prime);
	if (!prime) {
		static const std::array<movement, 4> moves {{
			{{face::front, direction::vertical, 0}, {face::down, direction::vertical, 0}},
			{{face::down, direction::vertical, 0}, {face::back, direction::vertical, length - 1}},
			{{face::back, direction::vertical, length - 1}, {face::up, direction::vertical, 0}},
			{{face::up, direction::vertical, 0}, {face::front, direction::vertical, 0}}
		}};
		move(moves);
	} else {
		static const std::array<movement, 4> moves {{
			{{face::front, direction::vertical, 0}, {face::up, direction::vertical, 0}},
			{{face::up, direction::vertical, 0}, {face::back, direction::vertical, length - 1}},
			{{face::back, direction::vertical, length - 1}, {face::down, direction::vertical, 0}},
			{{face::down, direction::vertical, 0}, {face::front, direction::vertical, 0}}
		}};
		move(moves);
	}
	return *this;
}

template <size_t length, typename tile_type>
cube<length, tile_type>& cube<length, tile_type>::turn_front(bool prime) {
	rotate_face(face::front, prime);
	if (!prime) {
		static const std::array<movement, 4> moves {{
			{{face::up, direction::horizontal, length - 1}, {face::right, direction::vertical, 0}},
			{{face::right, direction::vertical, 0}, {face::down, direction::horizontal, 0}},
			{{face::down, direction::horizontal, 0}, {face::left, direction::vertical, length - 1}},
			{{face::left, direction::vertical, length - 1}, {face::up, direction::horizontal, length - 1}}
		}};
		move(moves);
	} else {
		static const std::array<movement, 4> moves {{
			{{face::up, direction::horizontal, length - 1}, {face::left, direction::vertical, length - 1}},
			{{face::left, direction::vertical, length - 1}, {face::down, direction::horizontal, 0}},
			{{face::down, direction::horizontal, 0}, {face::right, direction::vertical, 0}},
			{{face::right, direction::vertical, 0}, {face::up, direction::horizontal, length - 1}}
		}};
		move(moves);
	}
	return *this;
}

template <size_t length, typename tile_type>
cube<length, tile_type>& cube<length, tile_type>::turn_back(bool prime) {
	rotate_face(face::back, prime);
	if (!prime) {
		static const std::array<movement, 4> moves {{
			{{face::up, direction::horizontal, 0}, {face::left, direction::vertical, 0}},
			{{face::left, direction::vertical, 0}, {face::down, direction::horizontal, length - 1}},
			{{face::down, direction::horizontal, length - 1}, {face::right, direction::vertical, length - 1}},
			{{face::right, direction::vertical, length - 1}, {face::up, direction::horizontal, 0}}
		}};
		move(moves);
	} else {
		static const std::array<movement, 4> moves {{
			{{face::up, direction::horizontal, 0}, {face::right, direction::vertical, length - 1}},
			{{face::right, direction::vertical, length - 1}, {face::down, direction::horizontal, length - 1}},
			{{face::down, direction::horizontal, length - 1}, {face::left, direction::vertical, 0}},
			{{face::left, direction::vertical, 0}, {face::up, direction::horizontal, 0}}
		}};
		move(moves);
	}
	return *this;
}

template <size_t length, typename tile_type>
const tile_type& cube<length, tile_type>::get_tile(face f, int row, int col) const {
	if (row >= length || row < 0) {
		throw std::out_of_range{"row out of range"};
	}
	if (col >= length || col < 0) {
		throw std::out_of_range{"col out of range"};
	}
	const int tile = row * length + col;
	return tile_data.at(to_int(f)).at(tile);
}

template <size_t length, typename tile_type>
tile_type& cube<length, tile_type>::get_tile(face f, int row, int col) {
	return const_cast<tile_type&>(const_cast<const cube*>(this)->get_tile());
}

template <size_t length, typename tile_type>
const std::array<tile_type, cube<length, tile_type>::tiles_per_face>&
cube<length, tile_type>::get_face(face f) const {
	return tile_data.at(to_int(f));
}

template <size_t length, typename tile_type>
std::array<tile_type, cube<length, tile_type>::tiles_per_face>&
cube<length, tile_type>::get_face(face f) {
	return tile_data.at(to_int(f));
}

template <size_t length, typename tile_type>
void cube<length, tile_type>::rotate_face(face f, bool prime) {
	rotate_ninety_degrees(get_face(f), length, length, prime);
}

template <size_t length, typename tile_type>
std::array<size_t, length> cube<length, tile_type>::get_indices(layer s) const {
	std::array<size_t, length> indices;
	if (is_column(s.sel)) {
		size_t start = to_int(s.sel.side) * tiles_per_face + s.offset;
		for (size_t i = 0; i < length; ++i) {
			indices[i] = start + i * length;
		}
	} else if (is_row(s.sel)) {
		size_t start = to_int(s.sel.side) * tiles_per_face + s.offset * length;
		for (size_t i = 0; i < length; ++i) {
			indices[i] = start + i;
		}
	} else {
		throw std::runtime_error{"unknown direction for selection"};
	}
	return indices;
}

template <size_t length, typename tile_type>
template <size_t size>
void cube<length, tile_type>::move(const std::array<movement, size>& moves) {
	const auto old_tile_data = tile_data;
	for (size_t i = 0; i < size; ++i) {
		const movement& move = moves[i];
		const auto source = get_indices(move.from);
		auto dest = get_indices(move.to);
		if (reversed(move)) {
			std::reverse(dest.begin(), dest.end());
		}
		for (size_t i = 0; i < length; ++i) {
			const size_t source_face = source[i] / tiles_per_face;
			const size_t source_tile = source[i] % tiles_per_face;
			const size_t dest_face = dest[i] / tiles_per_face;
			const size_t dest_tile = dest[i] % tiles_per_face;
			tile_data[dest_face][dest_tile] = old_tile_data[source_face][source_tile];
		}
	}
}

template <size_t length, typename tile_type>
std::ostream& operator<<(std::ostream& os, const cube<length, tile_type>& cube) {
	for (int face = 0; face < cube.face_count; ++face) {
		for (int row = 0; row < length; ++row) {
			for (int col = 0; col < length; ++col) {
				os << cube.get_tile(to_face(face), row, col).rep() << ' ';
			}
			os << '\n';
		}
		os << '\n';
	}
	return os;
}

}	// rubiks namespace

#endif
