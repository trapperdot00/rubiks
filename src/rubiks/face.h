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

constexpr int to_int(face f) {
	return static_cast<int>(f);
}

inline face to_face(int i) {
	if (i < to_int(face::up) || to_int(face::down) < i) {
		throw std::out_of_range{"face out of range"};
	}
	return face{i};
}

constexpr face opposite_face(face f) {
	switch (f) {
	case face::up:
		return face::down;
	case face::front:
		return face::back;
	case face::right:
		return face::left;
	case face::back:
		return face::front;
	case face::left:
		return face::right;
	case face::down:
		return face::up;
	}
}

}	// rubiks namespace

#endif
