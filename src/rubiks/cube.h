#ifndef CUBE_H
#define CUBE_H

#include "axis.h"
#include "rotation_pattern.h"
#include "movement.h"
#include "cube_utils.h"
#include "colored_tile.h"
#include "../utils/container_append.h"

#include <iostream>
#include <deque>
#include <vector>
#include <stdexcept>
#include <iterator>
#include <algorithm>

namespace rubiks {

template <size_t length, typename tile_type = colored_tile>
class cube {
public:
	cube() { reset(); }
	void reset();

	void turn(axis, size_t, bool prime = false);
	cube& turn_up(bool prime = false);
	cube& turn_down(bool prime = false);
	cube& turn_right(bool prime = false);
	cube& turn_left(bool prime = false);
	cube& turn_front(bool prime = false);
	cube& turn_back(bool prime = false);

	static constexpr size_t face_count = 6;
	static constexpr size_t tiles_per_face = length * length;
	
	const tile_type& get_tile(face f, int row, int col) const;
	tile_type& get_tile(face f, int row, int col);
	
	const std::array<tile_type, tiles_per_face>& get_face(face f) const;
	std::array<tile_type, tiles_per_face>& get_face(face f);

	std::array<std::array<tile_type, tiles_per_face>, face_count>& get() {
		return tile_data;
	}
private:
	void rotate_face(face f, bool prime = false);
	std::array<size_t, length> get_indices(layer) const;
	template <size_t size> void move(const std::array<movement, size>&);

	std::array<std::array<tile_type, tiles_per_face>, face_count> tile_data;
};

template <size_t length, typename tile_type>
std::ostream& operator<<(std::ostream&, const cube<length, tile_type>&);

}	// rubiks namespace

// Load template implementation
#include "cube.tpp"

#endif
