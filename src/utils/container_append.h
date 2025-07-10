#ifndef CONTAINER_APPEND_H
#define CONTAINER_APPEND_H

#include <utility>
#include <type_traits>

namespace utils {

template <typename Cont1, typename Cont2>
void append_from(Cont1&& from, Cont2& to) {
	using value_type = typename std::remove_reference_t<Cont1>::value_type;
	for (auto&& element : from) {
		to.push_back(std::forward<value_type>(element));
	}
}

}

#endif
