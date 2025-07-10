namespace rubiks {

template <typename tile_type>
cube_3x3<tile_type>& cube_3x3<tile_type>::turn_up() {
	rotate_face(tile_data.begin(),
				tile_data.begin() + 9,
				width(), height()
	);
	return *this;
}

}	// rubiks namespace
