#include "rubiks/cube.h"
#include "rubiks/colored_numbered_tile.h"

#include <map>
#include <random>
#include <chrono>

using namespace rubiks;

template <typename tile_type>
static const std::map<char, cube<tile_type>& (cube<tile_type>::*)(bool)>
turn_translation_table {
	{'u', &cube<tile_type>::turn_up},
	{'d', &cube<tile_type>::turn_down},
	{'r', &cube<tile_type>::turn_right},
	{'l', &cube<tile_type>::turn_left},
	{'f', &cube<tile_type>::turn_front},
	{'b', &cube<tile_type>::turn_back},
};

template <typename tile_type>
void game(cube<tile_type>& c) {
	const auto& turn_table = turn_translation_table<tile_type>;
	std::cout << c << '\n';
	std::cout << "enter movement: ";
	for (std::string cmd; std::cin >> cmd; ) {
		if (cmd.empty()) {
			continue;
		}
		char dir = std::tolower(cmd[0]);
		if (auto it = turn_table.find(dir); it != turn_table.cend()) {
			bool prime = (cmd.size() > 1 && cmd[1] == '\'');
			(c.*it->second)(prime);
		} else {
			std::cout << "invalid command: " << cmd << '\n';
		}
		std::cout << c << '\n';
		std::cout << "enter movement: ";
	}
}

template <typename tile_type>
void shuffle(cube<tile_type>& c, const size_t move_count = 20) {
	const auto& turn_table = turn_translation_table<tile_type>;
	static std::default_random_engine rand_engine(
		std::chrono::high_resolution_clock::now().time_since_epoch().count()
	);
	static std::uniform_int_distribution<size_t> index_gen(0, 5);
	static std::bernoulli_distribution prime_gen;

	std::cout << "SHUFFLING: ";
	for (size_t i = 0; i < move_count; ++i) {
		const size_t table_index = index_gen(rand_engine);
		const bool prime = prime_gen(rand_engine);
		auto it = turn_table.cbegin();
		std::advance(it, table_index);
		(c.*it->second)(prime);
		std::cout << char(std::toupper(it->first)) << (prime ? "'" : "") << ' ';
	}
	std::cout << "\n\n";
}

int main() {
	rubiks::cube cube{3};
	//shuffle(cube);
	game(cube);
}
