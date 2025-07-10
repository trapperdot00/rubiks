#ifndef CUBE_BASE_H
#define CUBE_BASE_H

#include "tile_base.h"
#include "face.h"
#include "slice.h"

#include <vector>
#include <memory>
#include <stdexcept>
#include <iterator>
#include <utility>

namespace rubiks {

class cube_base {
public:
	cube_base(int face_count, int tile_per_face) :
		face_no{face_count},
		tpf{tile_per_face}
	{}
	int face_num() const { return face_no; }
	int tiles_per_face() const { return tpf; }
	int tile_num() const {
		return face_num() * tiles_per_face();
	}

	virtual int width() const = 0;
	virtual int height() const = 0;
	virtual std::shared_ptr<tile_base> operator[](int) const = 0;
	virtual ~cube_base() = default;
private:
	int face_no;
	int tpf;
};

template <typename tile_type>
std::vector<std::shared_ptr<tile_base>>
init_tile_data(int fn, int tpf);

template <typename It>
void rotate_face(It b, It e, int w, int h, bool reverse = false);

}	// rubiks namespace

// Load template implementation
#include "cube_base.tpp"

#endif
