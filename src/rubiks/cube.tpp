#ifndef CUBE_TPP
#define CUBE_TPP

namespace rubiks {

template <typename tile_type>
cube<tile_type>::cube(size_t length) :
	length_{length},
	tile_data(face_count(), face_container(tiles_per_face()))
{
	reset();
}

template <typename tile_type>
void cube<tile_type>::reset() {
	for (size_t face = 0; face < face_count(); ++face) {
		for (size_t tile = 0; tile < tiles_per_face(); ++tile) {
			tile_data[face][tile] = tile_type{face, tile};
		}
	}
}

template <typename tile_type>
bool cube<tile_type>::solved() const {
	for (size_t i = 0; i < face_count(); ++i) {
		if (std::adjacent_find(tile_data[i].cbegin(),
			tile_data[i].cend(),
			[](const auto& a, const auto& b) {
				return a != b;
			}) != tile_data[i].cend())
		{
			return false;
		}
	}
	return true;
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
	std::vector<index_container> indices;
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
	std::vector<index_container> indices;
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
	std::vector<index_container> indices;
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
const tile_type& cube<tile_type>::get_tile(face f, size_t row, size_t col) const {
	if (row >= length()) {
		throw std::out_of_range{"row out of range"};
	}
	if (col >= length()) {
		throw std::out_of_range{"col out of range"};
	}
	const int tile = row * length() + col;
	return tile_data.at(to_int(f)).at(tile);
}

template <typename tile_type>
tile_type& cube<tile_type>::get_tile(face f, size_t row, size_t col) {
	return const_cast<tile_type&>(
		const_cast<const cube*>(this)->get_tile(f, row, col)
	);
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
typename cube<tile_type>::index_container cube<tile_type>::get_indices(layer s) const {
	index_container indices(length());
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

}	// rubiks namespace

#endif
