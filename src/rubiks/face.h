#ifndef FACE_H
#define FACE_H

#include <stdexcept>

namespace rubiks {

enum class face {
	up,
	front,
	right,
	back,
	left,
	down
};

constexpr int to_int(face f) { return static_cast<int>(f); }

inline face to_face(int i) {
	if (i < to_int(face::up) || to_int(face::down) < i) {
		throw std::out_of_range{"face out of range"};
	}
	return face{i};
}

}	// rubiks namespace

#endif
