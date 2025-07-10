namespace rubiks {

template <typename tile_type>
cube_3x3<tile_type>& cube_3x3<tile_type>::turn_up() {
	rotate_face(tile_data.begin(),
				tile_data.begin() + 9,
				width(), height()
	);
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
	int t_idx = block_length;
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

}	// rubiks namespace
