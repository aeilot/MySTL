//
// Created by Chenluo Deng on 3/9/26.
//

#ifndef MY_STL_CONCEPT_H
#define MY_STL_CONCEPT_H
#include <iostream>

namespace DS {
	template<class U>
	concept Streamable = requires(std::ostream& os, const U& x) {
		{ os << x } -> std::same_as<std::ostream&>;
	};
}

#endif //MY_STL_CONCEPT_H