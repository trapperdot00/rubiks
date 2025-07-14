#ifndef ROTATION_PATTERN_H
#define ROTATION_PATTERN_H

#include "selection.h"

#include <array>

namespace rubiks {

struct rotation_pattern {
	std::array<selection, 4> pattern;
};

// F
constexpr rotation_pattern x_axis_cw_rotation {{{
	{face::up, direction::horizontal},
	{face::right, direction::vertical},
	{face::down, direction::horizontal},
	{face::left, direction::vertical}
}}};

// F'
constexpr rotation_pattern x_axis_ccw_rotation {{{
	{face::up, direction::horizontal},
	{face::left, direction::vertical},
	{face::down, direction::horizontal},
	{face::right, direction::vertical}
}}};

// L
constexpr rotation_pattern y_axis_cw_rotation {{{
	{face::front, direction::vertical},
	{face::down, direction::vertical},
	{face::back, direction::vertical},
	{face::up, direction::vertical}
}}};

// L'
constexpr rotation_pattern y_axis_ccw_rotation {{{
	{face::front, direction::vertical},
	{face::up, direction::vertical},
	{face::back, direction::vertical},
	{face::down, direction::vertical}
}}};

// U
constexpr rotation_pattern z_axis_cw_rotation {{{
	{face::front, direction::horizontal},
	{face::left, direction::horizontal},
	{face::back, direction::horizontal},
	{face::right, direction::horizontal}
}}};

// U'
constexpr rotation_pattern z_axis_ccw_rotation {{{
	{face::front, direction::horizontal},
	{face::right, direction::horizontal},
	{face::back, direction::horizontal},
	{face::left, direction::horizontal}
}}};

}	// rubiks namespace

#endif
