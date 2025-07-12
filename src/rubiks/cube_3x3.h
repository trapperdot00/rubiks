#ifndef CUBE_3X3_H
#define CUBE_3X3_H

#include "cube_utils.h"
#include "tile_base.h"
#include "face.h"
#include "slice.h"
#include "../utils/container_append.h"

#include <iostream>
#include <deque>
#include <vector>
#include <stdexcept>
#include <iterator>

namespace rubiks {

template <typename tile_type>
class cube_3x3 {
public:
	cube_3x3() { reset(); }
	void reset();

	cube_3x3& turn_up(bool prime = false);
	cube_3x3& turn_down(bool prime = false);
	cube_3x3& turn_right(bool prime = false);
	cube_3x3& turn_left(bool prime = false);
	cube_3x3& turn_front(bool prime = false);
	cube_3x3& turn_back(bool prime = false);

	static constexpr int width = 3;
	static constexpr int height = 3;
	static constexpr int face_count = 6;
	static constexpr int tiles_per_face = width * height;
	
	const tile_type& get_tile(face f, int row, int col) const;
	tile_type& get_tile(face f, int row, int col);
	
	std::array<tile_type, width> get_row(face f, int row);
	std::array<tile_type, height> get_col(face f, int col);

	const std::array<tile_type, tiles_per_face>& get_face(face f) const;
	std::array<tile_type, tiles_per_face>& get_face(face f);

	std::array<std::array<tile_type, tiles_per_face>, face_count>& get() {
		return tile_data;
	}
private:
	std::array<std::array<tile_type, tiles_per_face>, face_count> tile_data;
};

template <typename tile_type>
std::ostream& operator<<(std::ostream&, const cube_3x3<tile_type>&);

}	// rubiks namespace

// Load template implementation
#include "cube_3x3.tpp"

#endif
