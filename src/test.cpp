#include <array>
#include <algorithm>
#include <iostream>
#include <string>

void initialize_face(std::array<std::string, 9>& face, char c) {
	for (int i = 0; i < 9; ++i) {
		face[i] = std::string{c} + std::to_string(i);
	}
}

void initialize_cube
(std::array<std::array<std::string, 9>, 6>& cube, const std::array<char, 6>& colors) {
	for (int i = 0; i < 6; ++i) {
		initialize_face(cube[i], colors[i]);
	}
}

std::ostream& print_face(std::ostream& os, const std::array<std::string, 9>& face) {
	for (int i = 0; i < 9; ++i) {
		if (i) {
			os << ' ';
		}
		os << face[i];
	}
	return os;
}

std::ostream& print_cube
(std::ostream& os, const std::array<std::array<std::string, 9>, 6>& cube) {
	for (int i = 0; i < 6; ++i) {
		print_face(os, cube[i]) << '\n';
	}
	return os << "------------------------------\n";
}

enum class face {
	top, front, right, back, left, down
};

enum class slice {
	top_row, bottom_row,
	left_column, right_column
};

bool is_row(slice s) {
	return s == slice::top_row || s == slice::bottom_row;
}

bool is_column(slice s) {
	return s == slice::left_column || s == slice::right_column;
}

int to_row_int(slice s) {
	switch (s) {
	case slice::top_row:
		return 0;
	case slice::bottom_row:
		return 2;
	default:
		throw 0;
	}
}

int to_column_int(slice s) {
	switch (s) {
	case slice::left_column:
		return 0;
	case slice::right_column:
		return 2;
	default:
		throw 0;
	}
}

struct movement {
	face from_face;
	slice from_slice;
	face to_face;
	slice to_slice;
};

constexpr int row_size = 3;
constexpr int column_size = 3;
constexpr int face_size = 9;

std::array<int, row_size> get_row_indices(face f, int row) {
	std::array<int, row_size> ret;
	int start = static_cast<int>(f) * face_size + row * row_size;
	for (int i = 0; i < row_size; ++i) {
		ret[i] = start++;
	}
	return ret;
}

std::array<int, column_size> get_column_indices(face f, int col) {
	std::array<int, column_size> ret;
	int start = static_cast<int>(f) * face_size + col;
	for (int i = 0; i < column_size; ++i) {
		ret[i] = start + i * row_size;
	}
	return ret;
}

std::array<int, 3> to_indices(face f, slice s) {
	std::array<int, 3> ret;
	if (is_row(s)) {
		ret = get_row_indices(f, to_row_int(s));
	} else if (is_column(s)) {
		ret = get_column_indices(f, to_column_int(s));
	} else {
		throw 0;
	}
	return ret;
}

bool have_to_reverse(slice from, slice to) {
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

template <size_t size>
void move(std::array<std::array<std::string, 9>, 6>& cube, const std::array<movement, size>& moves) {
	std::array<std::array<std::string, 9>, 6> old{cube};
	for (size_t i = 0; i < size; ++i) {
		const movement& m = moves[i];
		std::array<int, 3> from = to_indices(m.from_face, m.from_slice);
		std::array<int, 3> to = to_indices(m.to_face, m.to_slice);
		if (have_to_reverse(m.from_slice, m.to_slice)) {
			std::reverse(to.begin(), to.end());
		}
		for (int i = 0; i < 3; ++i) {
			cube[to[i] / 9][to[i] % 9] = old[from[i] / 9][from[i] % 9];
		}
	}
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

void test_movements(std::array<std::array<std::string, 9>, 6>& cube) {
	for (std::string cmd; std::cout << "enter movement: ", std::cin >> cmd; ) {
		std::array<std::array<std::string, 9>, 6> cube_cpy{cube};
		std::transform(cmd.cbegin(), cmd.cend(), 
					   cmd.begin(), [](char c) { return std::tolower(c); });
		try {
			std::array<movement, 4> m = parse_movement(cmd);
			move(cube_cpy, m);
			print_cube(std::cout, cube_cpy);
		} catch (...) {
			std::cout << "invalid movement\n";
		}
	}
}

int main() {
	std::array<char, 6> colors = {'y','r','g','o','b','w'};
	std::array<std::array<std::string, 9>, 6> cube;
	initialize_cube(cube, colors);
	print_cube(std::cout, cube);

	test_movements(cube);
}
