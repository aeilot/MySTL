//
// Created by Chenluo Deng on 3/9/26.
//

#ifndef MY_STL_LIST_H
#define MY_STL_LIST_H
#include <optional>

namespace DS {
	template<class T>
	class list {
	public:
		virtual ~list() {};

		virtual void clear() = 0;
		virtual void insert(size_t i, const T& x) = 0;
		virtual void remove(size_t i) = 0;
		virtual size_t length() const noexcept = 0;
		virtual std::optional<size_t> search(const T& x) const = 0;
		virtual T& at(size_t i) const = 0;
	};

}

#endif //MY_STL_LIST_H