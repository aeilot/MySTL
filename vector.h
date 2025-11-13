//
// Created by Chenluo Deng on 11/13/25.
//

#ifndef DS_VECTOR_H
#define DS_VECTOR_H
#include "concepts.h"

namespace MySTL::DS {
	template <class T>
	requires (MySTL::Copy<T> || MySTL::Move<T>)
	class vector {
		int sz;
		T* data;
	public:
		vector(): sz(0), data(nullptr) {
		}

		int size() const {
			return this->sz;
		}
	};
} // DS

#endif //DS_VECTOR_H