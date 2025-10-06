#ifndef CUBE_H
#define CUBE_H

#include "axis.h"
#include "movement.h"
#include "mapping.h"
#include "cube_utils.h"
#include "../tile/colored_tile.h"

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

	explicit cube(size_t length);

	// State altering and query
	void reset();
	bool solved() const;
	cube& turn(axis ax, size_t offset, bool ccw = false);
	
	// General information
	size_t length() const;
	size_t tiles_per_face() const;
	static constexpr size_t face_count();

	// Tile-getters
	const tile_type& get_tile(face side, size_t row, size_t col) const;
	tile_type& get_tile(face side, size_t row, size_t col);
	const face_container& get_face(face side) const;
	face_container& get_face(face side);
	cube_container& get();
private:
	void reset_face(size_t face);

	// Face rotation
	void rotate_face(face side, bool ccw = false);
	void rotate_face_if_offset_at_edge(axis turn_axis, size_t offset, bool ccw);

	// Full rotation
	void move(axis ax, const std::vector<index_container>& indices, bool ccw);
	void apply_movement(const index_container& src, const index_container& dest,
						const cube_container& old_tile_data,
						bool reverse = false);

	// Helpers
	std::vector<index_container> get_turn_affected_tiles(axis ax, size_t offset) const;
	std::array<mapping, 4> get_turn_mappings(axis ax) const;
	index_container get_indices(layer) const;
	size_t translate_offset(axis turn_axis, size_t i, size_t offset) const;
	selection get_turn_selection(axis turn_axis, size_t i) const;

	// Data
	size_t length_;
	cube_container tile_data;
};

}	// rubiks namespace

#include "cube_public.tpp"
#include "cube_private.tpp"

#endif
