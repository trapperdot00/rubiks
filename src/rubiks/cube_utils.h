#ifndef CUBE_UTILS_H
#define CUBE_UTILS_H

#include <cstddef>
#include <array>
#include <memory>
#include <utility>

namespace rubiks {

template <typename T, size_t size>
void rotate_ninety_degrees(std::array<T, size>&, int w, int h, bool r = false);

}	// rubiks namespace

#include "cube_utils.tpp"

#endif
