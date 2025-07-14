#ifndef TILE_BASE_H
#define TILE_BASE_H

#include <string>
#include <cstddef>

namespace rubiks {

class tile_base {
public:
	tile_base() = default;
	tile_base(size_t face, size_t tile) :
		face_no{face}, tile_no{tile}
	{}
	size_t face_num() const { return face_no; }
	size_t tile_num() const { return tile_no; }

	virtual std::string rep() const = 0;
	virtual ~tile_base() = default;
private:
	size_t face_no = 0;
	size_t tile_no = 0;
};

}	// rubiks namespace

#endif
