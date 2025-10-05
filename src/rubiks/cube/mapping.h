#ifndef MAPPING_H
#define MAPPING_H

#include <cstddef>

namespace rubiks {

struct mapping {
	size_t from;
	size_t to;
	bool reverse = false;
};

}	// rubiks namespace

#endif
