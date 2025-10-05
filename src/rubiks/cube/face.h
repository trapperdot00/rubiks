#ifndef FACE_H
#define FACE_H

namespace rubiks {

// Defines the six sides of a cube
// as symbolic constants
enum class face {
	up,
	front,
	right,
	back,
	left,
	down
};

// Converts a face to an integer
int to_int(face);

// Converts an integer to a face
face to_face(int);

// Returns the face opposite of the given face
face opposite_face(face);

}	// rubiks namespace

#endif
