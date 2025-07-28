#ifndef CUBE_H
#define CUBE_H

#include "axis.h"
#include "movement.h"
#include "cube_utils.h"
#include "colored_tile.h"
#include "../utils/container_append.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <cstddef>

namespace rubiks {

template <typename tile_type = colored_tile>
class cube {
public:
	using face_container = std::vector<tile_type>;
	using cube_container = std::vector<face_container>;
	using index_container = std::vector<size_t>;
	static constexpr size_t face_count = 6;

	cube(size_t);
	void reset();

	// TODO
	cube& turn(axis, size_t, bool prime = false);
	cube& turn_x_axis(size_t, bool prime = false);
	cube& turn_y_axis(size_t, bool prime = false);
	cube& turn_z_axis(size_t, bool prime = false);

	size_t length() const { return length_; }
	size_t tiles_per_face() const { return length_ * length_; }
	const tile_type& get_tile(face f, size_t row, size_t col) const;
	tile_type& get_tile(face f, size_t row, size_t col);
	const face_container& get_face(face f) const;
	face_container& get_face(face f);
	cube_container& get() { return tile_data; }
private:
	void rotate_face(face f, bool prime = false);
	index_container get_indices(layer) const;
	void apply_movement(const index_container&,
						const index_container&,
						const cube_container&,
						bool reverse = false);

	size_t length_;
	cube_container tile_data;
};

template <typename tile_type>
std::ostream& operator<<(std::ostream&, const cube<tile_type>&);

}	// rubiks namespace

// Load template implementation
#include "cube.tpp"

#endif
