#ifndef CUBE_3X3_H
#define CUBE_3X3_H

#include "cube_base.h"

#include <iostream>

namespace rubiks {

template <typename tile_type>
class cube_3x3 : public cube_base {
public:
	cube_3x3() :
		cube_base{6, 9},
		tile_data{init_tile_data<tile_type>(face_num(), tiles_per_face())}
	{}
	int width() const override { return 3; }
	int height() const override { return 3; }
	std::shared_ptr<tile_base> operator[](int i) const { return tile_data[i]; }

	cube_3x3& turn_up();
	cube_3x3& turn_down();
	cube_3x3& turn_right();
	cube_3x3& turn_left();
	cube_3x3& turn_front();
	cube_3x3& turn_back();
	
	cube_3x3& turn_up_prime();
	cube_3x3& turn_down_prime();
	cube_3x3& turn_right_prime();
	cube_3x3& turn_left_prime();
	cube_3x3& turn_front_prime();
	cube_3x3& turn_back_prime();
private:
	std::vector<std::shared_ptr<tile_base>> tile_data;
};

template <typename tile_type>
std::ostream& operator<<(std::ostream& os, const cube_3x3<tile_type>& cube) {
	const int fn = cube.face_num();
	const int tpf = cube.tiles_per_face();
	for (int face = 0; face < fn; ++face) {
		for (int tile = 0; tile < tpf; ++tile) {
			os << cube[face * tpf + tile]->rep();
		}
		os << '\n';
	}
	return os;
}

}	// rubiks namespace

// Load template implementation
#include "cube_3x3.tpp"

#endif
