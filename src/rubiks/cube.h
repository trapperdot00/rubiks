#ifndef CUBE_H
#define CUBE_H

#include "axis.h"
#include "rotation_pattern.h"
#include "movement.h"
#include "cube_utils.h"
#include "colored_tile.h"
#include "../utils/container_append.h"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iterator>
#include <algorithm>

namespace rubiks {

template <typename tile_type = colored_tile>
class cube {
public:
	using face_container = std::vector<tile_type>;
	using cube_container = std::vector<face_container>;
	static constexpr size_t face_count = 6;

	cube(size_t);
	void reset();

	void turn(axis, size_t, bool prime = false); // TODO
	cube& turn_up(bool prime = false);
	cube& turn_down(bool prime = false);
	cube& turn_right(bool prime = false);
	cube& turn_left(bool prime = false);
	cube& turn_front(bool prime = false);
	cube& turn_back(bool prime = false);

	size_t length() const { return length_; }
	size_t tiles_per_face() const { return length_ * length_; }
	const tile_type& get_tile(face f, int row, int col) const;
	tile_type& get_tile(face f, int row, int col);
	const face_container& get_face(face f) const;
	face_container& get_face(face f);
	cube_container& get() { return tile_data; }
private:
	void rotate_face(face f, bool prime = false);
	void move(const std::vector<movement>&);
	std::vector<size_t> get_indices(layer) const;

	size_t length_;
	cube_container tile_data;
};

template <typename tile_type>
std::ostream& operator<<(std::ostream&, const cube<tile_type>&);

}	// rubiks namespace

// Load template implementation
#include "cube.tpp"

#endif
