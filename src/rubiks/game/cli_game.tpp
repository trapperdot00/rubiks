template <typename tile_type>
void cli_game<tile_type>::shuffle(size_t steps) {
	static std::default_random_engine rand_engine(
		std::chrono::high_resolution_clock::now().time_since_epoch().count()
	);
	static std::uniform_int_distribution<int> axis_gen(0, 2);
	static std::bernoulli_distribution prime_gen;
	std::uniform_int_distribution<size_t> offset_gen(0, cube_ptr->length() - 1);
		std::cin.ignore(1, '\n');
	for (size_t i = 0; i < steps; ++i) {
		const axis ax = to_axis(axis_gen(rand_engine));
		const bool prime = prime_gen(rand_engine);
		const size_t offset = offset_gen(rand_engine);
		cube_ptr->turn(ax, offset, prime);
		std::cin.ignore(1, '\n');
	}
}

template <typename tile_type>
void cli_game<tile_type>::play() {
	print_cube(std::cout);
	do try {
		const auto [ax, offset, prime] = parse_rotation(std::cin);
		cube_ptr->turn(ax, offset, prime);
		print_cube(std::cout);
	} catch (const std::exception& err) {
		std::cerr << "error: " << err.what() << '\n';
	} while (std::cin && !solved());
}

template <typename tile_type>
std::ostream& cli_game<tile_type>::print_cube(std::ostream& os) const {
	for (size_t row = 0; row < cube_ptr->length(); ++row) {
		for (size_t col = 0; col < cube_ptr->length(); ++col) {
			os << std::setw(3) << cube_ptr->get_tile(face::up, row, col).rep();
		}
		os << '\n';
	}
	os << '\n';
	for (size_t row = 0; row < cube_ptr->length(); ++row) {
		for (size_t face = 1; face <= 4; ++face) {
			for (size_t col = 0; col < cube_ptr->length(); ++col) {
				os << std::setw(3) << cube_ptr->get_tile(to_face(face), row, col).rep();
			}
			os << "  ";
		}
		os << '\n';
	}
	os << '\n';
	for (size_t row = 0; row < cube_ptr->length(); ++row) {
		for (size_t col = 0; col < cube_ptr->length(); ++col) {
			os << std::setw(3) << cube_ptr->get_tile(face::down, row, col).rep();
		}
		os << '\n';
	}
	return os;
}

std::tuple<axis, size_t, bool> parse_rotation(std::istream& is) {
	axis ax = parse_axis(is);
	size_t offset = parse_offset(is);
	bool prime = parse_prime(is);
	return std::make_tuple(ax, offset, prime);
}

axis parse_axis(std::istream& is) {
	char ch = 0;
	if (!(is >> ch)) {
		throw std::runtime_error{"axis expected"};
	}
	return to_axis(ch);
}

size_t parse_offset(std::istream& is) {
	char ch = 0;
	if (!is.get(ch) || !(std::isdigit(ch))) {
		throw std::runtime_error{"number expected as offset"};
	}
	is.unget();
	size_t num = 0;
	is >> num;
	return num;
}

bool parse_prime(std::istream& is) {
	bool prime = false;
	char ch = 0;
	if (is.get(ch)) {
		if (ch == '\'') {
			prime = true;
		} else {
			is.unget();
		}
	}
	return prime;
}
