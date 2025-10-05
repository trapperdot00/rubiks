#include "movement.h"

namespace rubiks {

bool reversed(movement m) {
	if (m.from.sel.dir == m.to.sel.dir) {
		return m.from.offset != m.to.offset;
	}
	if (is_column(m.from.sel) != is_column(m.to.sel)) {
		return m.from.offset == m.to.offset;
	}
	return true;
}

}	// rubiks namespace
