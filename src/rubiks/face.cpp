#include "face.h"

#include <stdexcept>

namespace rubiks {

int to_int(face f) {
	return static_cast<int>(f);
}

face to_face(int i) {
	if (i < to_int(face::up) || to_int(face::down) < i) {
		throw std::out_of_range{"face out of range"};
	}
	return face{i};
}

}	// rubiks namespace
