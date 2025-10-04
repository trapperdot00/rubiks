#ifndef CUBE_H
#define CUBE_H

#include "axis.h"
#include "movement.h"
#include "mapping.h"
#include "cube_utils.h"
#include "colored_tile.h"

#include <vector>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <cstddef>
#include <utility>
#include <array>

namespace rubiks {

template <typename tile_type = colored_tile>
class cube {
public:
	using face_container = std::vector<tile_type>;
	using cube_container = std::vector<face_container>;
	using index_container = std::vector<size_t>;

	// Construct a cube of a given length
	cube(size_t);

	// Get the cube to the initial, solved position
	void reset();
	// Check whether the cube is solved
	bool solved() const;

	// Turns a layer of the cube specified by
	//  - an axis of rotation,
	//  - an offset from the cube's lower-left corner
	//  - a counterclockwise flag
	cube& turn(axis, size_t offset, bool ccw = false);
	
	// Rotates a layer about the X-axis
	// Clockwise rotations on a 2x2x2 cube:
	//  - offset of 0: L
	//  - offset of 1: R'
	cube& turn_x_axis(size_t offset, bool ccw = false);

	// Rotates a layer about the Y-axis
	// Clockwise rotations on a 2x2x2 cube:
	//  - offset of 0: F
	//  - offset of 1: B'
	cube& turn_y_axis(size_t offset, bool ccw = false);

	// Rotates a layer about the Z-axis
	// Clockwise rotations on a 2x2x2 cube:
	//  - offset of 0: D
	//  - offset of 1: U'
	cube& turn_z_axis(size_t offset, bool ccw = false);

	size_t length() const { return length_; }
	size_t tiles_per_face() const { return length_ * length_; }
	static constexpr size_t face_count() { return 6; }

	// Returns the tile fully specified by the side,
	// a row and a column
	const tile_type& get_tile(face side, size_t row, size_t col) const;
	tile_type& get_tile(face side, size_t row, size_t col);

	// Returns the tiles on a given side
	const face_container& get_face(face side) const;
	face_container& get_face(face side);

	// Returns all of the tiles
	cube_container& get() { return tile_data; }
private:
	// Rotates the top tiles of a side by 90 degrees
	// clockwise by default
	void rotate_face(face side, bool prime = false);

	// Copies the selected tiles from old_tile_data
	// into the current tile_data
	// The selected old tiles are denoted by the indices in src,
	// the new tiles' indices are denoted by dest
	// Copying is done incrementally, optionally in reverse order
	void apply_movement(const index_container& src,
						const index_container& dest,
						const cube_container& old_tile_data,
						bool reverse = false);

	// Returns the indices of a given column or row
	index_container get_indices(layer) const;

	void reset_face(size_t face);

	size_t length_;
	cube_container tile_data;
};

}	// rubiks namespace

// Load template implementation
#include "cube.tpp"

#endif
