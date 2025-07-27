#ifndef CUBE_UTILS_H
#define CUBE_UTILS_H

#include <cstddef>
#include <vector>
#include <memory>
#include <utility>

namespace rubiks {

template <typename T>
void rotate_ninety_degrees(std::vector<T>&, int w, int h, bool r = false);

}	// rubiks namespace

#include "cube_utils.tpp"

#endif
