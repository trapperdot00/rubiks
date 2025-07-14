#include <array>
#include <algorithm>
#include <iostream>
#include <string>

enum class face {
	top, front, right, back, left, down
};

enum class slice {
	top_row, bottom_row,
	left_column, right_column
};

constexpr bool is_row(slice s) {
	return s == slice::top_row || s == slice::bottom_row;
}

constexpr bool is_column(slice s) {
	return s == slice::left_column || s == slice::right_column;
}


struct movement {
	face from_face;
	slice from_slice;
	face to_face;
	slice to_slice;
};


template <size_t width>
struct cube {
	static constexpr size_t tpf = width * width;
	static constexpr std::array<char, 6> colors = {'y','r','g','o','b','w'};
	cube() {
		for (size_t i = 0; i < 6; ++i) {
			for (size_t j = 0; j < tpf; ++j) {
				faces[i][j] = std::string{colors[i]} + std::to_string(j);
			}
		}
	}
	constexpr int to_row_int(slice s) {
		switch (s) {
		case slice::top_row:
			return 0;
		case slice::bottom_row:
			return width - 1;
		}
		return -1;
	}
	constexpr int to_column_int(slice s) {
		switch (s) {
		case slice::left_column:
			return 0;
		case slice::right_column:
			return width - 1;
		}
		return -1;
	}
	constexpr bool have_to_reverse(slice from, slice to) {
		if (from == to) {
			return false;
		}
		if (is_column(from) && is_row(to)) {
			return to_column_int(from) == to_row_int(to);
		}
		if (is_row(from) && is_column(to)) {
			return to_row_int(from) == to_column_int(to);
		}
		return true;
	}
	std::array<size_t, width> get_row_indices(face f, size_t row) {
		std::array<size_t, width> ret;
		size_t begin = static_cast<size_t>(f) * tpf + row * width;
		for (size_t i = 0; i < width; ++i) {
			ret[i] = begin + i;
		}
		return ret;
	}
	std::array<size_t, width> get_column_indices(face f, size_t col) {
		std::array<size_t, width> ret;
		size_t begin = static_cast<size_t>(f) * tpf + col;
		for (size_t i = 0; i < width; ++i) {
			ret[i] = begin + i * width;
		}
		return ret;
	}
	std::array<size_t, width> to_indices(face f, slice s) {
		if (is_column(s)) {
			return get_column_indices(f, to_column_int(s));
		}
		if (is_row(s)) {
			return get_row_indices(f, to_row_int(s));
		}
		return {};
	}
	void move(std::array<movement, 4> moves) {
		auto old = faces;
		for (size_t i = 0; i < 4; ++i) {
			const movement& m = moves[i];
			std::array<size_t, width> from = to_indices(m.from_face, m.from_slice);
			std::array<size_t, width> to = to_indices(m.to_face, m.to_slice);
			if (have_to_reverse(m.from_slice, m.to_slice)) {
				std::reverse(to.begin(), to.end());
			}
			for (int i = 0; i < width; ++i) {
				faces[to[i] / tpf][to[i] % tpf] = old[from[i] / tpf][from[i] % tpf];
			}
		}
	}
	std::array<std::array<std::string, tpf>, 6> faces;
};

template <size_t width>
std::ostream& operator<<(std::ostream& os, const cube<width>& c) {
	for (size_t i = 0; i < 6; ++i) {
		for (size_t j = 0; j < c.tpf; ++j) {
			os << c.faces[i][j] << ' ';
		}
		os << '\n';
	}
	return os;
}

constexpr std::array<movement, 4> U {{
	{face::front, slice::top_row, face::left, slice::top_row},
	{face::left, slice::top_row, face::back, slice::top_row},
	{face::back, slice::top_row, face::right, slice::top_row},
	{face::right, slice::top_row, face::front, slice::top_row}
}};
constexpr std::array<movement, 4> U_prime {{
	{face::front, slice::top_row, face::right, slice::top_row},
	{face::right, slice::top_row, face::back, slice::top_row},
	{face::back, slice::top_row, face::left, slice::top_row},
	{face::left, slice::top_row, face::front, slice::top_row}
}};

constexpr std::array<movement, 4> D {{
	{face::front, slice::bottom_row, face::right, slice::bottom_row},
	{face::right, slice::bottom_row, face::back, slice::bottom_row},
	{face::back, slice::bottom_row, face::left, slice::bottom_row},
	{face::left, slice::bottom_row, face::front, slice::bottom_row}
}};
constexpr std::array<movement, 4> D_prime {{
	{face::front, slice::bottom_row, face::left, slice::bottom_row},
	{face::left, slice::bottom_row, face::back, slice::bottom_row},
	{face::back, slice::bottom_row, face::right, slice::bottom_row},
	{face::right, slice::bottom_row, face::front, slice::bottom_row}
}};

constexpr std::array<movement, 4> R {{
	{face::front, slice::right_column, face::top, slice::right_column},
	{face::top, slice::right_column, face::back, slice::left_column},
	{face::back, slice::left_column, face::down, slice::right_column},
	{face::down, slice::right_column, face::front, slice::right_column}
}};
constexpr std::array<movement, 4> R_prime {{
	{face::front, slice::right_column, face::down, slice::right_column},
	{face::down, slice::right_column, face::back, slice::left_column},
	{face::back, slice::left_column, face::top, slice::right_column},
	{face::top, slice::right_column, face::front, slice::right_column}
}};

constexpr std::array<movement, 4> L {{
	{face::front, slice::left_column, face::down, slice::left_column},
	{face::down, slice::left_column, face::back, slice::right_column},
	{face::back, slice::right_column, face::top, slice::left_column},
	{face::top, slice::left_column, face::front, slice::left_column}
}};
constexpr std::array<movement, 4> L_prime {{
	{face::front, slice::left_column, face::top, slice::left_column},
	{face::top, slice::left_column, face::back, slice::right_column},
	{face::back, slice::right_column, face::down, slice::left_column},
	{face::down, slice::left_column, face::front, slice::left_column}
}};

constexpr std::array<movement, 4> F {{
	{face::top, slice::bottom_row, face::right, slice::left_column},
	{face::right, slice::left_column, face::down, slice::top_row},
	{face::down, slice::top_row, face::left, slice::right_column},
	{face::left, slice::right_column, face::top, slice::bottom_row}
}};
constexpr std::array<movement, 4> F_prime {{
	{face::top, slice::bottom_row, face::left, slice::right_column},
	{face::left, slice::right_column, face::down, slice::top_row},
	{face::down, slice::top_row, face::right, slice::left_column},
	{face::right, slice::left_column, face::top, slice::bottom_row}
}};

constexpr std::array<movement, 4> B {{
	{face::top, slice::top_row, face::left, slice::left_column},
	{face::left, slice::left_column, face::down, slice::bottom_row},
	{face::down, slice::bottom_row, face::right, slice::right_column},
	{face::right, slice::right_column, face::top, slice::top_row}
}};
constexpr std::array<movement, 4> B_prime {{
	{face::top, slice::top_row, face::right, slice::right_column},
	{face::right, slice::right_column, face::down, slice::bottom_row},
	{face::down, slice::bottom_row, face::left, slice::left_column},
	{face::left, slice::left_column, face::top, slice::top_row}
}};

std::array<movement, 4> parse_movement(const std::string& cmd) {
	if (cmd == "u") {
		return U;
	} else if (cmd == "u'") {
		return U_prime;
	} else if (cmd == "d") {
		return D;
	} else if (cmd == "d'") {
		return D_prime;
	} else if (cmd == "r") {
		return R;
	} else if (cmd == "r'") {
		return R_prime;
	} else if (cmd == "l") {
		return L;
	} else if (cmd == "l'") {
		return L_prime;
	} else if (cmd == "f") {
		return F;
	} else if (cmd == "f'") {
		return F_prime;
	} else if (cmd == "b") {
		return B;
	} else if (cmd == "b'") {
		return B_prime;
	} else {
		throw 0;
	}
}

void test_movements() {
	cube<3> c;
	std::cout << c << '\n';
	for (std::string cmd; std::cout << "enter movement: ", std::cin >> cmd; ) {
		std::transform(cmd.cbegin(), cmd.cend(), 
					   cmd.begin(), [](char c) { return std::tolower(c); });
		try {
			std::array<movement, 4> m = parse_movement(cmd);
			c.move(m);
			std::cout << c << '\n';
		} catch (...) {
			std::cout << "invalid movement\n";
		}
	}
}

int main() {
	test_movements();
}
