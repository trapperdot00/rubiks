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
		reset_face(face);
	}
}

template <typename tile_type>
void cube<tile_type>::reset_face(size_t face) {
	for (size_t tile = 0; tile < tiles_per_face(); ++tile) {
		tile_data[face][tile] = tile_type{face, tile};
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
	if (offset >= length()) {
		throw std::out_of_range{"layer offset out of range"};
	}
	std::vector<index_container> indices = get_turn_affected_tiles(axis::x, offset);
	rotate_face_if_offset_at_edge(axis::x, offset, prime);
	move(axis::x, indices, prime);
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_y_axis(size_t offset, bool prime) {
	if (offset >= length()) {
		throw std::out_of_range{"layer offset out of range"};
	}
	std::vector<index_container> indices = get_turn_affected_tiles(axis::y, offset);
	rotate_face_if_offset_at_edge(axis::y, offset, prime);
	move(axis::y, indices, prime);
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_z_axis(size_t offset, bool prime) {
	if (offset >= length()) {
		throw std::out_of_range{"layer offset out of range"};
	}
	std::vector<index_container> indices = get_turn_affected_tiles(axis::z, offset);
	rotate_face_if_offset_at_edge(axis::z, offset, prime);
	move(axis::z, indices, prime);
	return *this;
}

template <typename tile_type>
void cube<tile_type>::move
(axis ax, const std::vector<index_container>& indices, bool prime) {
	const auto old_cube = tile_data;
	for (mapping m : get_turn_mappings(ax)) {
		if (prime) {
			std::swap(m.from, m.to);
		}
		apply_movement(indices[m.from], indices[m.to], old_cube, m.reverse);
	}
}

template <typename tile_type>
std::array<mapping, 4> cube<tile_type>::get_turn_mappings(axis ax) const {
	static constexpr std::array<mapping, 4> x_mappings{{
		{2, 0, true},
		{0, 1},
		{3, 2, true},
		{1, 3}
	}};
	static constexpr std::array<mapping, 4> y_mappings{{
		{2, 0, true},
		{0, 1},
		{3, 2},
		{1, 3, true}
	}};
	static constexpr std::array<mapping, 4> z_mappings{{
		{3, 0},
		{0, 1},
		{1, 2},
		{2, 3}
	}};
	switch (ax) {
	case axis::x:
		return x_mappings;
	case axis::y:
		return y_mappings;
	case axis::z:
		return z_mappings;
	default:
		throw std::invalid_argument{"invalid axis"};
	}
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
std::vector<typename cube<tile_type>::index_container>
cube<tile_type>::get_turn_affected_tiles(axis ax, size_t offset) const {
	std::vector<index_container> result;
	result.reserve(4 * length());
	for (size_t i = 0; i < 4; ++i) {
		selection curr_selection = get_turn_selection(ax, i);
		size_t curr_offset = translate_offset(ax, i, offset);
		layer curr_layer{curr_selection, curr_offset};
		index_container affected_tiles = get_indices(curr_layer);
		result.push_back(std::move(affected_tiles));
	}
	return result;
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
void cube<tile_type>::rotate_face_if_offset_at_edge(axis ax, size_t offset, bool prime) {
	if (offset == 0) {
		switch (ax) {
		case axis::x:
			rotate_face(face::left, prime);
			break;
		case axis::y:
			rotate_face(face::front, prime);
			break;
		case axis::z:
			rotate_face(face::down, prime);
			break;
		default:
			throw std::invalid_argument{"invalid axis"};
		}
	} else if (offset == length() - 1) {
		switch (ax) {
		case axis::x:
			rotate_face(face::right, !prime);
			break;
		case axis::y:
			rotate_face(face::back, !prime);
			break;
		case axis::z:
			rotate_face(face::up, !prime);
			break;
		default:
			throw std::invalid_argument{"invalid axis"};
		}
	}
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

template <typename tile_type>
size_t cube<tile_type>::translate_offset(axis ax, size_t i, size_t offset) const {
	if (i > 3) {
		throw std::out_of_range{"i out of range"};
	}
	switch (ax) {
	case axis::x:
		return (i == 2) ? (length() - offset - 1) : offset;
	case axis::y:
		return (i % 2 == 0) ? (length() - offset - 1) : offset;
	case axis::z:
		return length() - offset - 1;
	default:
		throw std::runtime_error{"invalid axis"};
	}
}

template <typename tile_type>
selection cube<tile_type>::get_turn_selection(axis ax, size_t i) const {
	static constexpr std::array<face, 4> x_faces {
		face::up, face::front, face::back, face::down
	};
	static constexpr std::array<face, 4> y_faces {
		face::up, face::right, face::left, face::down
	};
	static constexpr std::array<face, 4> z_faces {
		face::front, face::right, face::back, face::left
	};
	if (i > 3) {
		throw std::out_of_range{"i out of range"};
	}
	switch (ax) {
	case axis::x:
		return selection{x_faces[i], direction::vertical};
	case axis::y:
		if (i == 0 || i == 3) {
			return selection{y_faces[i], direction::horizontal};
		}
		return selection{y_faces[i], direction::vertical};
	case axis::z:
		return selection{z_faces[i], direction::horizontal};
	default:
		throw std::runtime_error{"invalid axis"};
	}
}

}	// rubiks namespace

#endif
