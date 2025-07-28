#ifndef CUBE_TPP
#define CUBE_TPP

namespace rubiks {

template <typename tile_type> cube<tile_type>::cube(size_t length) :
	length_{length},
	tile_data(face_count, face_container(tiles_per_face()))
{
	reset();
}

template <typename tile_type> void cube<tile_type>::reset() {
	for (size_t face = 0; face < face_count; ++face) {
		for (size_t tile = 0; tile < tiles_per_face(); ++tile) {
			tile_data[face][tile] = tile_type{face, tile};
		}
	}
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn(axis ax, size_t offset, bool prime) {
	if (offset >= length()) {
		throw std::out_of_range{"layer offset out of range"};
	}
	switch (ax) {
	case axis::x:
		return turn_x_axis(offset, prime);
	case axis::y:
		return turn_y_axis(offset, prime);
	case axis::z:
		return turn_z_axis(offset, prime);
	default:
		throw std::runtime_error{"invalid axis"};
	}
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_x_axis(size_t offset, bool prime) {
	const auto old_cube = tile_data;
	std::vector<std::vector<size_t>> indices;
	indices.push_back(get_indices(layer{selection{face::up, direction::vertical}, offset}));
	indices.push_back(get_indices(layer{selection{face::front, direction::vertical}, offset}));
	indices.push_back(get_indices(layer{selection{face::back, direction::vertical}, length() - offset - 1}));
	indices.push_back(get_indices(layer{selection{face::down, direction::vertical}, offset}));
	if (!offset) {
		rotate_face(face::left, prime);
	} else if (offset == length() - 1) {
		rotate_face(face::right, !prime);
	}
	apply_movement(indices[2], indices[0], old_cube, true);
	apply_movement(indices[0], indices[1], old_cube);
	apply_movement(indices[3], indices[2], old_cube, true);
	apply_movement(indices[1], indices[3], old_cube);
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_y_axis(size_t offset, bool prime) {
	const auto old_cube = tile_data;
	std::vector<std::vector<size_t>> indices;
	indices.push_back(get_indices(layer{selection{face::up, direction::horizontal}, length() - offset - 1}));
	indices.push_back(get_indices(layer{selection{face::right, direction::vertical}, offset}));
	indices.push_back(get_indices(layer{selection{face::left, direction::vertical}, length() - offset - 1}));
	indices.push_back(get_indices(layer{selection{face::down, direction::horizontal}, offset}));
	if (!offset) {
		rotate_face(face::front, prime);
	} else if (offset == length() - 1) {
		rotate_face(face::back, !prime);
	}
	apply_movement(indices[2], indices[0], old_cube, true);
	apply_movement(indices[0], indices[1], old_cube);
	apply_movement(indices[3], indices[2], old_cube);
	apply_movement(indices[1], indices[3], old_cube, true);
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_z_axis(size_t offset, bool prime) {
	const auto old_cube = tile_data;
	std::vector<std::vector<size_t>> indices;
	indices.push_back(get_indices(layer{selection{face::front, direction::horizontal}, length() - offset - 1}));
	indices.push_back(get_indices(layer{selection{face::right, direction::horizontal}, length() - offset - 1}));
	indices.push_back(get_indices(layer{selection{face::back, direction::horizontal}, length() - offset - 1}));
	indices.push_back(get_indices(layer{selection{face::left, direction::horizontal}, length() - offset - 1}));
	if (!offset) {
		rotate_face(face::down, prime);
	} else if (offset == length() - 1) {
		rotate_face(face::up, !prime);
	}
	apply_movement(indices[3], indices[0], old_cube);
	apply_movement(indices[0], indices[1], old_cube);
	apply_movement(indices[1], indices[2], old_cube);
	apply_movement(indices[2], indices[3], old_cube);
	return *this;
}

template <typename tile_type>
void cube<tile_type>::apply_movement(const index_container& src_indices,
									 const index_container& dest_indices,
									 const cube_container& old_cube,
									 bool reverse) {
	if (src_indices.size() != length() || dest_indices.size() != length()) {
		throw std::runtime_error{"index size mismatch"};
	}
	auto src_i = reverse ? length() - 1 : 0;
	auto dest_i = 0;
	for (size_t i = 0; i < length(); ++i) {
		const size_t src = src_indices[src_i];
		const size_t dest = dest_indices[dest_i];
		const size_t face_dest = dest / tiles_per_face();
		const size_t tile_dest = dest % tiles_per_face();
		auto& current_tile = tile_data[face_dest][tile_dest];
		const size_t face_src = src / tiles_per_face();
		const size_t tile_src = src % tiles_per_face();
		const auto& old_tile = old_cube[face_src][tile_src];
		current_tile = old_tile;
		if (!reverse) {
			++src_i;
		} else {
			--src_i;
		}
		++dest_i;
	}
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_up(bool prime) {
	rotate_face(face::up, prime);
	if (!prime) {
		static const std::vector<movement> moves {{
			{{face::front, direction::horizontal, 0}, {face::left, direction::horizontal, 0}},
			{{face::left, direction::horizontal, 0}, {face::back, direction::horizontal, 0}},
			{{face::back, direction::horizontal, 0}, {face::right, direction::horizontal, 0}},
			{{face::right, direction::horizontal, 0}, {face::front, direction::horizontal, 0}}
		}};
		move(moves);
	} else {
		static const std::vector<movement> moves {{
			{{face::front, direction::horizontal, 0}, {face::right, direction::horizontal, 0}},
			{{face::right, direction::horizontal, 0}, {face::back, direction::horizontal, 0}},
			{{face::back, direction::horizontal, 0}, {face::left, direction::horizontal, 0}},
			{{face::left, direction::horizontal, 0}, {face::front, direction::horizontal, 0}}
		}};
		move(moves);
	}
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_down(bool prime) {
	rotate_face(face::down, prime);
	if (!prime) {
		static const std::vector<movement> moves {{
			{{face::front, direction::horizontal, length() - 1}, {face::right, direction::horizontal, length() - 1}},
			{{face::right, direction::horizontal, length() - 1}, {face::back, direction::horizontal, length() - 1}},
			{{face::back, direction::horizontal, length() - 1}, {face::left, direction::horizontal, length() - 1}},
			{{face::left, direction::horizontal, length() - 1}, {face::front, direction::horizontal, length() - 1}}
		}};
		move(moves);
	} else {
		static const std::vector<movement> moves {{
			{{face::front, direction::horizontal, length() - 1}, {face::left, direction::horizontal, length() - 1}},
			{{face::left, direction::horizontal, length() - 1}, {face::back, direction::horizontal, length() - 1}},
			{{face::back, direction::horizontal, length() - 1}, {face::right, direction::horizontal, length() - 1}},
			{{face::right, direction::horizontal, length() - 1}, {face::front, direction::horizontal, length() - 1}}
		}};
		move(moves);
	}
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_right(bool prime) {
	rotate_face(face::right, prime);
	if (!prime) {
		static const std::vector<movement> moves {{
			{{face::front, direction::vertical, length() - 1}, {face::up, direction::vertical, length() - 1}},
			{{face::up, direction::vertical, length() - 1}, {face::back, direction::vertical, 0}},
			{{face::back, direction::vertical, 0}, {face::down, direction::vertical, length() - 1}},
			{{face::down, direction::vertical, length() - 1}, {face::front, direction::vertical, length() - 1}}
		}};
		move(moves);
	} else {
		static const std::vector<movement> moves {{
			{{face::front, direction::vertical, length() - 1}, {face::down, direction::vertical, length() - 1}},
			{{face::down, direction::vertical, length() - 1}, {face::back, direction::vertical, 0}},
			{{face::back, direction::vertical, 0}, {face::up, direction::vertical, length() - 1}},
			{{face::up, direction::vertical, length() - 1}, {face::front, direction::vertical, length() - 1}}
		}};
		move(moves);
	}
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_left(bool prime) {
	rotate_face(face::left, prime);
	if (!prime) {
		static const std::vector<movement> moves {{
			{{face::front, direction::vertical, 0}, {face::down, direction::vertical, 0}},
			{{face::down, direction::vertical, 0}, {face::back, direction::vertical, length() - 1}},
			{{face::back, direction::vertical, length() - 1}, {face::up, direction::vertical, 0}},
			{{face::up, direction::vertical, 0}, {face::front, direction::vertical, 0}}
		}};
		move(moves);
	} else {
		static const std::vector<movement> moves {{
			{{face::front, direction::vertical, 0}, {face::up, direction::vertical, 0}},
			{{face::up, direction::vertical, 0}, {face::back, direction::vertical, length() - 1}},
			{{face::back, direction::vertical, length() - 1}, {face::down, direction::vertical, 0}},
			{{face::down, direction::vertical, 0}, {face::front, direction::vertical, 0}}
		}};
		move(moves);
	}
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_front(bool prime) {
	rotate_face(face::front, prime);
	if (!prime) {
		static const std::vector<movement> moves {{
			{{face::up, direction::horizontal, length() - 1}, {face::right, direction::vertical, 0}},
			{{face::right, direction::vertical, 0}, {face::down, direction::horizontal, 0}},
			{{face::down, direction::horizontal, 0}, {face::left, direction::vertical, length() - 1}},
			{{face::left, direction::vertical, length() - 1}, {face::up, direction::horizontal, length() - 1}}
		}};
		move(moves);
	} else {
		static const std::vector<movement> moves {{
			{{face::up, direction::horizontal, length() - 1}, {face::left, direction::vertical, length() - 1}},
			{{face::left, direction::vertical, length() - 1}, {face::down, direction::horizontal, 0}},
			{{face::down, direction::horizontal, 0}, {face::right, direction::vertical, 0}},
			{{face::right, direction::vertical, 0}, {face::up, direction::horizontal, length() - 1}}
		}};
		move(moves);
	}
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_back(bool prime) {
	rotate_face(face::back, prime);
	if (!prime) {
		static const std::vector<movement> moves {{
			{{face::up, direction::horizontal, 0}, {face::left, direction::vertical, 0}},
			{{face::left, direction::vertical, 0}, {face::down, direction::horizontal, length() - 1}},
			{{face::down, direction::horizontal, length() - 1}, {face::right, direction::vertical, length() - 1}},
			{{face::right, direction::vertical, length() - 1}, {face::up, direction::horizontal, 0}}
		}};
		move(moves);
	} else {
		static const std::vector<movement> moves {{
			{{face::up, direction::horizontal, 0}, {face::right, direction::vertical, length() - 1}},
			{{face::right, direction::vertical, length() - 1}, {face::down, direction::horizontal, length() - 1}},
			{{face::down, direction::horizontal, length() - 1}, {face::left, direction::vertical, 0}},
			{{face::left, direction::vertical, 0}, {face::up, direction::horizontal, 0}}
		}};
		move(moves);
	}
	return *this;
}

template <typename tile_type>
const tile_type& cube<tile_type>::get_tile(face f, int row, int col) const {
	if (row >= length() || row < 0) {
		throw std::out_of_range{"row out of range"};
	}
	if (col >= length() || col < 0) {
		throw std::out_of_range{"col out of range"};
	}
	const int tile = row * length() + col;
	return tile_data.at(to_int(f)).at(tile);
}

template <typename tile_type>
tile_type& cube<tile_type>::get_tile(face f, int row, int col) {
	return const_cast<tile_type&>(const_cast<const cube*>(this)->get_tile());
}

template <typename tile_type>
const typename cube<tile_type>::face_container&
cube<tile_type>::get_face(face f) const {
	return tile_data.at(to_int(f));
}

template <typename tile_type>
typename cube<tile_type>::face_container&
cube<tile_type>::get_face(face f) {
	return tile_data.at(to_int(f));
}

template <typename tile_type>
void cube<tile_type>::rotate_face(face f, bool prime) {
	rotate_ninety_degrees(get_face(f), length(), length(), prime);
}

template <typename tile_type>
std::vector<size_t> cube<tile_type>::get_indices(layer s) const {
	std::vector<size_t> indices(length());
	if (is_column(s.sel)) {
		size_t start = to_int(s.sel.side) * tiles_per_face() + s.offset;
		for (size_t i = 0; i < length(); ++i) {
			indices[i] = start + i * length();
		}
	} else if (is_row(s.sel)) {
		size_t start = to_int(s.sel.side) * tiles_per_face() + s.offset * length();
		for (size_t i = 0; i < length(); ++i) {
			indices[i] = start + i;
		}
	} else {
		throw std::runtime_error{"unknown direction for selection"};
	}
	return indices;
}

template <typename tile_type>
void cube<tile_type>::move(const std::vector<movement>& moves) {
	const auto old_tile_data = tile_data;
	for (size_t i = 0; i < moves.size(); ++i) {
		const movement& move = moves[i];
		const auto source = get_indices(move.from);
		auto dest = get_indices(move.to);
		if (reversed(move)) {
			std::reverse(dest.begin(), dest.end());
		}
		for (size_t i = 0; i < length(); ++i) {
			const size_t source_face = source[i] / tiles_per_face();
			const size_t source_tile = source[i] % tiles_per_face();
			const size_t dest_face = dest[i] / tiles_per_face();
			const size_t dest_tile = dest[i] % tiles_per_face();
			tile_data[dest_face][dest_tile] = old_tile_data[source_face][source_tile];
		}
	}
}

template <typename tile_type>
std::ostream& operator<<(std::ostream& os, const cube<tile_type>& cube) {
	for (int row = 0; row < cube.length(); ++row) {
		for (int col = 0; col < cube.length(); ++col) {
			os << std::setw(3) << cube.get_tile(to_face(0), row, col).rep() << ' ';
		}
		os << '\n';
	}
	os << '\n';
	for (int row = 0; row < cube.length(); ++row) {
		for (int face = 1; face <= 4; ++face) {
			for (int col = 0; col < cube.length(); ++col) {
				os << std::setw(3) << cube.get_tile(to_face(face), row, col).rep() << ' ';
			}
			os << "  ";
		}
		os << '\n';
	}
	os << '\n';
	for (int row = 0; row < cube.length(); ++row) {
		for (int col = 0; col < cube.length(); ++col) {
			os << std::setw(3) << cube.get_tile(to_face(5), row, col).rep() << ' ';
		}
		os << '\n';
	}
	return os;
}

}	// rubiks namespace

#endif
