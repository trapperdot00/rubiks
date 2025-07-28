template <typename tile_type>
void cli_game<tile_type>::shuffle(size_t steps) {
	static std::default_random_engine rand_engine(
		std::chrono::high_resolution_clock::now().time_since_epoch().count()
	);
	static std::uniform_int_distribution<int> axis_gen(0, 2);
	static std::bernoulli_distribution prime_gen;
	std::uniform_int_distribution<size_t> offset_gen(0, cube_ptr->length() - 1);
	std::cout << "shuffling...\n";
	for (size_t i = 0; i < steps; ++i) {
		const axis ax = to_axis(axis_gen(rand_engine));
		const bool prime = prime_gen(rand_engine);
		const size_t offset = offset_gen(rand_engine);
		std::cout << '(' << to_char(ax) << offset << (prime ? "'" : "") << ")\n";
		cube_ptr->turn(ax, offset, prime);
		print_cube(std::cout) << '\n';
		char a;
		std::cin >> a;
	}
}

template <typename tile_type>
void cli_game<tile_type>::play() {
	shuffle();
	print_cube(std::cout);
	while (!solved()) try {
		char ch1 = 0;
		if (!(std::cin >> ch1)) {
			return;
		}
		axis ax = to_axis(ch1);
		size_t offset = 0;
		if (!(std::cin >> offset)) {
			return;
		}
		char ch2 = 0;
		bool prime = false;
		if (std::cin >> ch2 && ch2 == '\'') {
			prime = true;
		}
		cube_ptr->turn(ax, offset, prime);
		print_cube(std::cout);
	} catch (const std::exception& err) {
		std::cerr << "error: " << err.what() << '\n';
	}
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
