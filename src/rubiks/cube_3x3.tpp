#ifndef CUBE_3X3_TPP
#define CUBE_3X3_TPP

#include "../utils/container_append.h"

namespace rubiks {

template <typename tile_type>
void cube_3x3<tile_type>::rotate_face(face f, bool prime) {
	if (to_int(f) < to_int(face::up) || to_int(f) > to_int(face::down)) {
		throw std::out_of_range{"face_no out of range"};
	}
	auto first = tile_data.begin();
	std::advance(first, tiles_per_face() * to_int(f));
	auto last = first;
	std::advance(last, tiles_per_face());
	rubiks::rotate_face(first, last, width(), height(), prime);
}

template <typename tile_type>
cube_3x3<tile_type>& cube_3x3<tile_type>::turn_up(bool prime) {
	rotate_face(face::up, prime);
	static constexpr int changing_tiles = 12;
	static constexpr int block_length = 3;
	std::vector<std::shared_ptr<tile_base>> temp;
	temp.reserve(changing_tiles);
	const int tpf = tiles_per_face();
	int idx = tpf;
	for (int i = 0; i < changing_tiles; ++i) {
		temp.push_back(std::move(tile_data[idx]));
		if ((idx + 1) % block_length == 0) {
			idx += tpf - block_length;
		}
		++idx;
	}
	idx = tpf;
	int t_idx = prime ? changing_tiles - block_length : block_length;
	for (int i = 0; i < changing_tiles; ++i) {
		tile_data[idx] = std::move(temp[t_idx]);
		if ((idx + 1) % block_length == 0) {
			idx += tpf - block_length;
		}
		if (t_idx == changing_tiles - 1) {
			t_idx = 0;
		} else {
			++t_idx;
		}
		++idx;
	}
	return *this;
}

template <typename tile_type>
cube_3x3<tile_type>& cube_3x3<tile_type>::turn_down(bool prime) {
	rotate_face(face::down, prime);
	static constexpr int changing_tiles = 12;
	static constexpr int block_length = 3;
	std::vector<std::shared_ptr<tile_base>> temp;
	temp.reserve(changing_tiles);
	const int tpf = tiles_per_face();
	int idx = 2 * tpf - block_length;
	for (int i = 0; i < changing_tiles; ++i) {
		temp.push_back(std::move(tile_data[idx]));
		if ((idx + 1) % block_length == 0) {
			idx += tpf - block_length;
		}
		++idx;
	}
	int t_idx = prime ? block_length : changing_tiles - block_length;
	idx = 2 * tpf - block_length;
	for (int i = 0; i < changing_tiles; ++i) {
		tile_data[idx] = std::move(temp[t_idx]);
		if ((idx + 1) % block_length == 0) {
			idx += tpf - block_length;
		}
		if (t_idx == changing_tiles - 1) {
			t_idx = 0;
		} else {
			++t_idx;
		}
		++idx;
	}
	return *this;
}

template <typename tile_type>
cube_3x3<tile_type>& cube_3x3<tile_type>::turn_right(bool prime) {
	rotate_face(face::right, prime);
	auto temp = extract_tiles(face::up, slice::right_column);
	utils::append_from(extract_tiles(face::front, slice::right_column), temp);
	utils::append_from(extract_tiles(face::back, slice::left_column), temp);

	const int w = width();
	const int h = height();
	const int tpf = tiles_per_face();

	// Add down face's rightmost tiles
	{
	int idx = to_int(face::down) * tpf;
	for (int i = w - 1; i < tpf; i += w) {
		temp.push_back(std::move(tile_data[idx + i]));
	}
	}
	
	// Change top face's rightmost tiles
	{
	int idx = to_int(face::up) * tpf;
	int t_idx = 3;
	for (int i = w - 1; i < tpf; i += w) {
		tile_data[idx + i] = std::move(temp[t_idx]);
		++t_idx;
	}
	}
	// Change front face's rightmost tiles
	{
	int idx = to_int(face::front) * tpf;
	int t_idx = 9;
	for (int i = w - 1; i < tpf; i += w) {
		tile_data[idx + i] = std::move(temp[t_idx]);
		++t_idx;
	}
	}
	// Change back face's leftmost tiles
	{
	int idx = to_int(face::back) * tpf;
	int t_idx = 2;
	for (int i = 0; i < tpf; i += w) {
		tile_data[idx + i] = std::move(temp[t_idx]);
		--t_idx;
	}
	}
	// Change down face's rightmost tiles
	{
	int idx = to_int(face::down) * tpf;
	int t_idx = 8;
	for (int i = w - 1; i < tpf; i += w) {
		tile_data[idx + i] = std::move(temp[t_idx]);
		--t_idx;
	}
	}

	return *this;
}

template <typename tile_type>
std::vector<std::shared_ptr<tile_base>>
cube_3x3<tile_type>::extract_tiles(face side, slice cut) {
	const bool horizontal = is_horizontal(cut);
	const int begin = to_int(side) * tiles_per_face();
	const int end = begin + tiles_per_face();
	const int distance = horizontal ? 1 : width();
	const int offset = horizontal ? to_int(cut) * width()
							: cut - slice::left_column;
	std::vector<std::shared_ptr<tile_base>> ret;
	for (int tile = begin + offset; tile < end; tile += distance) {
		ret.push_back(std::move(tile_data[tile]));
	}
	return ret;
}

template <typename tile_type>
std::ostream& operator<<(std::ostream& os, const cube_3x3<tile_type>& cube) {
	const int fn = cube.face_num();
	const int tpf = cube.tiles_per_face();
	for (int face = 0; face < fn; ++face) {
		for (int tile = 0; tile < tpf; ++tile) {
			auto p = cube[face * tpf + tile];
			if (p) {
				os << p->rep() << ' ';
			} else {
				throw std::runtime_error{"nullptr in tile_data"};
			}
		}
		os << '\n';
	}
	return os;
}

}	// rubiks namespace

#endif
