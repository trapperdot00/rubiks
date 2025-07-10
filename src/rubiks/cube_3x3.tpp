#ifndef CUBE_3X3_TPP
#define CUBE_3X3_TPP

namespace rubiks {

template <typename tile_type>
void cube_3x3<tile_type>::rotate_face(int face_no, bool prime) {
	if (face_no < 0 || face_no >= face_num()) {
		throw std::out_of_range{"face_no out of range"};
	}
	auto first = tile_data.begin();
	std::advance(first, tiles_per_face() * face_no);
	auto last = first;
	std::advance(last, tiles_per_face());
	rubiks::rotate_face(first, last, width(), height(), prime);
}

template <typename tile_type>
cube_3x3<tile_type>& cube_3x3<tile_type>::turn_up(bool prime) {
	rotate_face(0, prime);
	static constexpr int changing_tiles = 12;
	static constexpr int block_length = 3;
	std::vector<std::shared_ptr<tile_base>> temp;
	temp.reserve(changing_tiles);
	const int tpf = tiles_per_face();
	for (int idx = tpf, i = 0; i < changing_tiles; ++i, ++idx) {
		temp.push_back(std::move(tile_data[idx]));
		if ((idx + 1) % block_length == 0) {
			idx += tpf - block_length;
		}
	}
	int t_idx = prime ? changing_tiles - block_length : block_length;
	for (int idx = tpf, i = 0; i < changing_tiles; ++i, ++idx) {
		tile_data[idx] = std::move(temp[t_idx]);
		if ((idx + 1) % block_length == 0) {
			idx += tpf - block_length;
		}
		if (t_idx == changing_tiles - 1) {
			t_idx = 0;
		} else {
			++t_idx;
		}
	}
	return *this;
}

template <typename tile_type>
cube_3x3<tile_type>& cube_3x3<tile_type>::turn_down(bool prime) {
	rotate_face(5, prime);
	static constexpr int changing_tiles = 12;
	static constexpr int block_length = 3;
	std::vector<std::shared_ptr<tile_base>> temp;
	temp.reserve(changing_tiles);
	const int tpf = tiles_per_face();
	for (int idx = 2 * tpf - block_length, i = 0; i < changing_tiles; ++i, ++idx) {
		temp.push_back(std::move(tile_data[idx]));
		if ((idx + 1) % block_length == 0) {
			idx += tpf - block_length;
		}
	}
	int t_idx = prime ? block_length : changing_tiles - block_length;
	for (int idx = 2 * tpf - block_length, i = 0; i < changing_tiles; ++i, ++idx) {
		tile_data[idx] = std::move(temp[t_idx]);
		if ((idx + 1) % block_length == 0) {
			idx += tpf - block_length;
		}
		if (t_idx == changing_tiles - 1) {
			t_idx = 0;
		} else {
			++t_idx;
		}
	}
	return *this;
}

}	// rubiks namespace

#endif
