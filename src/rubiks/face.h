#ifndef FACE_H
#define FACE_H

namespace rubiks {

enum class face {
	up,
	front,
	right,
	back,
	left,
	down
};

int to_int(face);
face to_face(int);
face opposite_face(face);

}	// rubiks namespace

#endif
