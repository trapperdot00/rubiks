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
	std::shared_ptr<tile_base> operator[](int i) const override { return tile_data[i]; }

	cube_3x3& turn_up(bool prime = false);
	cube_3x3& turn_down(bool prime = false);
	cube_3x3& turn_right(bool prime = false);
	cube_3x3& turn_left(bool prime = false);
	cube_3x3& turn_front(bool prime = false);
	cube_3x3& turn_back(bool prime = false);
private:
	void rotate_face(face n, bool prime = false);
	std::vector<std::shared_ptr<tile_base>> extract_tiles(face n, slice o);

	std::vector<std::shared_ptr<tile_base>> tile_data;
};

template <typename tile_type>
std::ostream& operator<<(std::ostream&, const cube_3x3<tile_type>&);

}	// rubiks namespace

// Load template implementation
#include "cube_3x3.tpp"

#endif
