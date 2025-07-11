#ifndef CUBE_3X3_H
#define CUBE_3X3_H

#include "tile_base.h"
#include "face.h"
#include "slice.h"
#include "../utils/container_append.h"

#include <iostream>
#include <array>
#include <deque>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iterator>
#include <utility>

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
	
	std::weak_ptr<tile_base> get_tile(face f, int row, int col) const;
	std::array<std::shared_ptr<tile_base>, width> get_row(face f, int row) const;
	std::array<std::shared_ptr<tile_base>, height> get_col(face f, int col) const;
	std::array<std::shared_ptr<tile_base>, tiles_per_face> get_face(face f) const
		{ return tile_data.at(to_int(f)); }
	std::array<std::array<std::shared_ptr<tile_base>, tiles_per_face>, face_count> get() const
		{ return tile_data; }
private:
	void rotate_face(face n, bool prime = false);

	std::array<std::array<std::shared_ptr<tile_base>, tiles_per_face>, face_count> tile_data;
};

template <typename tile_type>
std::ostream& operator<<(std::ostream&, const cube_3x3<tile_type>&);

}	// rubiks namespace

// Load template implementation
#include "cube_3x3.tpp"

#endif
