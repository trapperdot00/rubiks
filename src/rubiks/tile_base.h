#ifndef TILE_BASE_H
#define TILE_BASE_H

#include <string>

namespace rubiks {

class tile_base {
public:
	tile_base(int face, int tile) :
		face_no{face}, tile_no{tile}
	{}
	int face_num() const { return face_no; }
	int tile_num() const { return tile_no; }

	virtual std::string rep() const = 0;
	virtual ~tile_base() = default;
private:
	int face_no;
	int tile_no;
};

};	// rubiks namespace

#endif
