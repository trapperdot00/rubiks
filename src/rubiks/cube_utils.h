#ifndef CUBE_UTILS_H
#define CUBE_UTILS_H

#include <cstddef>
#include <vector>
#include <memory>
#include <utility>

namespace rubiks {

// Rotates a given one-dimensional sequence of elements
// of a rectangle by ninety degrees
// Takes a flag to rotate it counterclockwise
// Works on squares as well as rectangles
template <typename T>
void rotate_ninety_degrees(std::vector<T>&, int w, int h, bool ccw = false);

}	// rubiks namespace

#include "cube_utils.tpp"

#endif
