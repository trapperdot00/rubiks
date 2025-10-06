#ifndef CUBE_PUBLIC_TPP
#define CUBE_PUBLIC_TPP

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
	std::vector<index_container> indices = get_turn_affected_tiles(ax, offset);
	rotate_face_if_offset_at_edge(ax, offset, prime);
	move(ax, indices, prime);
	return *this;
}

template <typename tile_type>
size_t cube<tile_type>::length() const {
	return length_;
}

template <typename tile_type>
size_t cube<tile_type>::tiles_per_face() const {
	return length_ * length_;
}

template <typename tile_type>
constexpr size_t cube<tile_type>::face_count() {
	return 6;
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
typename cube<tile_type>::cube_container& cube<tile_type>::get() {
	return tile_data;
}

}	// rubiks namespace

#endif
