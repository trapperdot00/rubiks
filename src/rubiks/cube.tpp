#ifndef CUBE_TPP
#define CUBE_TPP

namespace rubiks {

template <typename tile_type> cube<tile_type>::cube(size_t length) :
	length_{length},
	tile_data(face_count, face_container(tiles_per_face()))
{
	reset();
}

template <typename tile_type> void cube<tile_type>::reset() {
	for (size_t face = 0; face < face_count; ++face) {
		for (size_t tile = 0; tile < tiles_per_face(); ++tile) {
			tile_data[face][tile] = tile_type{face, tile};
		}
	}
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn(axis ax, size_t offset, bool prime) {
	if (offset >= length()) {
		throw std::out_of_range{"layer offset out of range"};
	}
	switch (ax) {
	case axis::x:
		return turn_x_axis(offset, prime);
	case axis::y:
		return turn_y_axis(offset, prime);
	case axis::z:
		return turn_z_axis(offset, prime);
	default:
		throw std::runtime_error{"invalid axis"};
	}
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_x_axis(size_t offset, bool prime) {
	std::vector<size_t> top_indices = get_indices(layer{selection{face::up, direction::vertical}, offset});
	std::vector<size_t> front_indices = get_indices(layer{selection{face::front, direction::vertical}, offset});
	std::vector<size_t> back_indices = get_indices(layer{selection{face::back, direction::vertical}, length() - offset - 1});
	std::vector<size_t> bottom_indices = get_indices(layer{selection{face::down, direction::vertical}, offset});
	std::cout << "top_indices:";
	for (size_t i : top_indices) {
		std::cout << ' ' << i;
	}
	std::cout << '\n';
	std::cout << "front_indices:";
	for (size_t i : front_indices) {
		std::cout << ' ' << i;
	}
	std::cout << '\n';
	std::cout << "back_indices:";
	for (size_t i : back_indices) {
		std::cout << ' ' << i;
	}
	std::cout << '\n';
	std::cout << "bottom_indices:";
	for (size_t i : bottom_indices) {
		std::cout << ' ' << i;
	}
	std::cout << '\n';
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_y_axis(size_t offset, bool prime) {
	std::vector<size_t> top_indices = get_indices(layer{selection{face::up, direction::horizontal}, length() - offset - 1});
	std::vector<size_t> right_indices = get_indices(layer{selection{face::right, direction::vertical}, offset});
	std::vector<size_t> left_indices = get_indices(layer{selection{face::left, direction::vertical}, length() - offset - 1});
	std::vector<size_t> bottom_indices = get_indices(layer{selection{face::down, direction::horizontal}, offset});
	std::cout << "top_indices:";
	for (size_t i : top_indices) {
		std::cout << ' ' << i;
	}
	std::cout << '\n';
	std::cout << "right_indices:";
	for (size_t i : right_indices) {
		std::cout << ' ' << i;
	}
	std::cout << '\n';
	std::cout << "left_indices:";
	for (size_t i : left_indices) {
		std::cout << ' ' << i;
	}
	std::cout << '\n';
	std::cout << "bottom_indices:";
	for (size_t i : bottom_indices) {
		std::cout << ' ' << i;
	}
	std::cout << '\n';
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_z_axis(size_t offset, bool prime) {
	std::vector<size_t> front_indices = get_indices(layer{selection{face::front, direction::horizontal}, length() - offset - 1});
	std::vector<size_t> right_indices = get_indices(layer{selection{face::right, direction::horizontal}, length() - offset - 1});
	std::vector<size_t> back_indices = get_indices(layer{selection{face::back, direction::horizontal}, length() - offset - 1});
	std::vector<size_t> left_indices = get_indices(layer{selection{face::left, direction::horizontal}, length() - offset - 1});
	std::cout << "front_indices:";
	for (size_t i : front_indices) {
		std::cout << ' ' << i;
	}
	std::cout << '\n';
	std::cout << "right_indices:";
	for (size_t i : right_indices) {
		std::cout << ' ' << i;
	}
	std::cout << '\n';
	std::cout << "back_indices:";
	for (size_t i : back_indices) {
		std::cout << ' ' << i;
	}
	std::cout << '\n';
	std::cout << "left_indices:";
	for (size_t i : left_indices) {
		std::cout << ' ' << i;
	}
	std::cout << '\n';
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_up(bool prime) {
	rotate_face(face::up, prime);
	if (!prime) {
		static const std::vector<movement> moves {{
			{{face::front, direction::horizontal, 0}, {face::left, direction::horizontal, 0}},
			{{face::left, direction::horizontal, 0}, {face::back, direction::horizontal, 0}},
			{{face::back, direction::horizontal, 0}, {face::right, direction::horizontal, 0}},
			{{face::right, direction::horizontal, 0}, {face::front, direction::horizontal, 0}}
		}};
		move(moves);
	} else {
		static const std::vector<movement> moves {{
			{{face::front, direction::horizontal, 0}, {face::right, direction::horizontal, 0}},
			{{face::right, direction::horizontal, 0}, {face::back, direction::horizontal, 0}},
			{{face::back, direction::horizontal, 0}, {face::left, direction::horizontal, 0}},
			{{face::left, direction::horizontal, 0}, {face::front, direction::horizontal, 0}}
		}};
		move(moves);
	}
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_down(bool prime) {
	rotate_face(face::down, prime);
	if (!prime) {
		static const std::vector<movement> moves {{
			{{face::front, direction::horizontal, length() - 1}, {face::right, direction::horizontal, length() - 1}},
			{{face::right, direction::horizontal, length() - 1}, {face::back, direction::horizontal, length() - 1}},
			{{face::back, direction::horizontal, length() - 1}, {face::left, direction::horizontal, length() - 1}},
			{{face::left, direction::horizontal, length() - 1}, {face::front, direction::horizontal, length() - 1}}
		}};
		move(moves);
	} else {
		static const std::vector<movement> moves {{
			{{face::front, direction::horizontal, length() - 1}, {face::left, direction::horizontal, length() - 1}},
			{{face::left, direction::horizontal, length() - 1}, {face::back, direction::horizontal, length() - 1}},
			{{face::back, direction::horizontal, length() - 1}, {face::right, direction::horizontal, length() - 1}},
			{{face::right, direction::horizontal, length() - 1}, {face::front, direction::horizontal, length() - 1}}
		}};
		move(moves);
	}
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_right(bool prime) {
	rotate_face(face::right, prime);
	if (!prime) {
		static const std::vector<movement> moves {{
			{{face::front, direction::vertical, length() - 1}, {face::up, direction::vertical, length() - 1}},
			{{face::up, direction::vertical, length() - 1}, {face::back, direction::vertical, 0}},
			{{face::back, direction::vertical, 0}, {face::down, direction::vertical, length() - 1}},
			{{face::down, direction::vertical, length() - 1}, {face::front, direction::vertical, length() - 1}}
		}};
		move(moves);
	} else {
		static const std::vector<movement> moves {{
			{{face::front, direction::vertical, length() - 1}, {face::down, direction::vertical, length() - 1}},
			{{face::down, direction::vertical, length() - 1}, {face::back, direction::vertical, 0}},
			{{face::back, direction::vertical, 0}, {face::up, direction::vertical, length() - 1}},
			{{face::up, direction::vertical, length() - 1}, {face::front, direction::vertical, length() - 1}}
		}};
		move(moves);
	}
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_left(bool prime) {
	rotate_face(face::left, prime);
	if (!prime) {
		static const std::vector<movement> moves {{
			{{face::front, direction::vertical, 0}, {face::down, direction::vertical, 0}},
			{{face::down, direction::vertical, 0}, {face::back, direction::vertical, length() - 1}},
			{{face::back, direction::vertical, length() - 1}, {face::up, direction::vertical, 0}},
			{{face::up, direction::vertical, 0}, {face::front, direction::vertical, 0}}
		}};
		move(moves);
	} else {
		static const std::vector<movement> moves {{
			{{face::front, direction::vertical, 0}, {face::up, direction::vertical, 0}},
			{{face::up, direction::vertical, 0}, {face::back, direction::vertical, length() - 1}},
			{{face::back, direction::vertical, length() - 1}, {face::down, direction::vertical, 0}},
			{{face::down, direction::vertical, 0}, {face::front, direction::vertical, 0}}
		}};
		move(moves);
	}
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_front(bool prime) {
	rotate_face(face::front, prime);
	if (!prime) {
		static const std::vector<movement> moves {{
			{{face::up, direction::horizontal, length() - 1}, {face::right, direction::vertical, 0}},
			{{face::right, direction::vertical, 0}, {face::down, direction::horizontal, 0}},
			{{face::down, direction::horizontal, 0}, {face::left, direction::vertical, length() - 1}},
			{{face::left, direction::vertical, length() - 1}, {face::up, direction::horizontal, length() - 1}}
		}};
		move(moves);
	} else {
		static const std::vector<movement> moves {{
			{{face::up, direction::horizontal, length() - 1}, {face::left, direction::vertical, length() - 1}},
			{{face::left, direction::vertical, length() - 1}, {face::down, direction::horizontal, 0}},
			{{face::down, direction::horizontal, 0}, {face::right, direction::vertical, 0}},
			{{face::right, direction::vertical, 0}, {face::up, direction::horizontal, length() - 1}}
		}};
		move(moves);
	}
	return *this;
}

template <typename tile_type>
cube<tile_type>& cube<tile_type>::turn_back(bool prime) {
	rotate_face(face::back, prime);
	if (!prime) {
		static const std::vector<movement> moves {{
			{{face::up, direction::horizontal, 0}, {face::left, direction::vertical, 0}},
			{{face::left, direction::vertical, 0}, {face::down, direction::horizontal, length() - 1}},
			{{face::down, direction::horizontal, length() - 1}, {face::right, direction::vertical, length() - 1}},
			{{face::right, direction::vertical, length() - 1}, {face::up, direction::horizontal, 0}}
		}};
		move(moves);
	} else {
		static const std::vector<movement> moves {{
			{{face::up, direction::horizontal, 0}, {face::right, direction::vertical, length() - 1}},
			{{face::right, direction::vertical, length() - 1}, {face::down, direction::horizontal, length() - 1}},
			{{face::down, direction::horizontal, length() - 1}, {face::left, direction::vertical, 0}},
			{{face::left, direction::vertical, 0}, {face::up, direction::horizontal, 0}}
		}};
		move(moves);
	}
	return *this;
}

template <typename tile_type>
const tile_type& cube<tile_type>::get_tile(face f, int row, int col) const {
	if (row >= length() || row < 0) {
		throw std::out_of_range{"row out of range"};
	}
	if (col >= length() || col < 0) {
		throw std::out_of_range{"col out of range"};
	}
	const int tile = row * length() + col;
	return tile_data.at(to_int(f)).at(tile);
}

template <typename tile_type>
tile_type& cube<tile_type>::get_tile(face f, int row, int col) {
	return const_cast<tile_type&>(const_cast<const cube*>(this)->get_tile());
}

template <typename tile_type>
const typename cube<tile_type>::face_container&
cube<tile_type>::get_face(face f) const {
	return tile_data.at(to_int(f));
}

template <typename tile_type>
typename cube<tile_type>::face_container&
cube<tile_type>::get_face(face f) {
	return tile_data.at(to_int(f));
}

template <typename tile_type>
void cube<tile_type>::rotate_face(face f, bool prime) {
	rotate_ninety_degrees(get_face(f), length(), length(), prime);
}

template <typename tile_type>
std::vector<size_t> cube<tile_type>::get_indices(layer s) const {
	std::vector<size_t> indices(length());
	if (is_column(s.sel)) {
		size_t start = to_int(s.sel.side) * tiles_per_face() + s.offset;
		for (size_t i = 0; i < length(); ++i) {
			indices[i] = start + i * length();
		}
	} else if (is_row(s.sel)) {
		size_t start = to_int(s.sel.side) * tiles_per_face() + s.offset * length();
		for (size_t i = 0; i < length(); ++i) {
			indices[i] = start + i;
		}
	} else {
		throw std::runtime_error{"unknown direction for selection"};
	}
	return indices;
}

template <typename tile_type>
void cube<tile_type>::move(const std::vector<movement>& moves) {
	const auto old_tile_data = tile_data;
	for (size_t i = 0; i < moves.size(); ++i) {
		const movement& move = moves[i];
		const auto source = get_indices(move.from);
		auto dest = get_indices(move.to);
		if (reversed(move)) {
			std::reverse(dest.begin(), dest.end());
		}
		for (size_t i = 0; i < length(); ++i) {
			const size_t source_face = source[i] / tiles_per_face();
			const size_t source_tile = source[i] % tiles_per_face();
			const size_t dest_face = dest[i] / tiles_per_face();
			const size_t dest_tile = dest[i] % tiles_per_face();
			tile_data[dest_face][dest_tile] = old_tile_data[source_face][source_tile];
		}
	}
}

template <typename tile_type>
std::ostream& operator<<(std::ostream& os, const cube<tile_type>& cube) {
	for (int row = 0; row < cube.length(); ++row) {
		for (int col = 0; col < cube.length(); ++col) {
			os << cube.get_tile(to_face(0), row, col).rep() << ' ';
		}
		os << '\n';
	}
	os << '\n';
	for (int row = 0; row < cube.length(); ++row) {
		for (int face = 1; face <= 4; ++face) {
			for (int col = 0; col < cube.length(); ++col) {
				os << cube.get_tile(to_face(face), row, col).rep() << ' ';
			}
			os << "  ";
		}
		os << '\n';
	}
	os << '\n';
	for (int row = 0; row < cube.length(); ++row) {
		for (int col = 0; col < cube.length(); ++col) {
			os << cube.get_tile(to_face(5), row, col).rep() << ' ';
		}
		os << '\n';
	}
	return os;
}

}	// rubiks namespace

#endif
