//
// Created by Chenluo Deng on 3/9/26.
//

#ifndef MY_STL_VECTOR_H
#define MY_STL_VECTOR_H
#include <initializer_list>
#include <iostream>
#include <optional>
#include <memory>
#include <utility>
#include <stdexcept>

#include "list.h"
#include "../concept.h"

namespace DS {
	template <class T>
	class vector : public list<T> {
	private:
		T* data;
		size_t currentSize;
		size_t currentCapacity;
	public:
		using iterator = T*;
		using const_iterator = const T*;
		using value_type = T;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;
		using size_type = size_t;
		using difference_type = ptrdiff_t;

		size_t size() const noexcept {
			return currentSize;
		}

		size_t capacity() const noexcept {
			return currentCapacity;
		}

		vector() : data(nullptr), currentSize(0), currentCapacity(0) {};

		vector(size_t capa) : currentSize(0), currentCapacity(capa) {
			data = (capa > 0) ? static_cast<T*>(::operator new(capa * sizeof(T))) : nullptr;
		}

		vector(std::initializer_list<T> lst) {
			currentSize = lst.size();
			currentCapacity = currentSize*2;
			data = static_cast<T*>(::operator new(currentCapacity*sizeof(T)));
			try {
				std::uninitialized_copy(lst.begin(), lst.end(), data);
			} catch (...) {
				::operator delete(data);
				throw;
			}
		}

		vector(const vector<T>& other)
		: currentSize(other.currentSize), currentCapacity(other.currentCapacity) {
			data = static_cast<T*>(::operator new(currentCapacity * sizeof(T)));
			try {
				std::uninitialized_copy(other.data, other.data + currentSize, data);
			} catch (...) {
				::operator delete(data);
				throw;
			}
		}

		// vector(const vector<T>& lst) {
		// 	currentSize = lst.size();
		// 	currentCapacity = lst.capacity();
		// 	data = static_cast<T*>(::operator new(currentCapacity*sizeof(T)));
		// 	for (int i = 0; i < currentSize; i++) {
		// 		new (data+i) T(lst[i]);
		// 	}
		// }

		vector(vector<T>&& lst) noexcept :
		data(std::exchange(lst.data, nullptr)),
		currentSize(std::exchange(lst.currentSize,0)),
		currentCapacity(std::exchange(lst.currentCapacity,0))
		{}

		// vector(vector<T>&& lst) noexcept {
		// 	currentSize = lst.size();
		// 	currentCapacity = lst.capacity();
		// 	data = lst.data;
		// 	lst.data = nullptr;
		// 	lst.currentSize = 0;
		// 	lst.currentCapacity = 0;
		// }

		~vector() {
			// for (int i = 0; i < currentSize; ++i) {
			// 	data[i].~T();
			// }
			std::destroy(data, data + currentSize);
			::operator delete(data);
		}

		void swap(vector& other) noexcept {
			std::swap(data, other.data);
			std::swap(currentSize, other.currentSize);
			std::swap(currentCapacity, other.currentCapacity);
		}

		// Pass by value, Copy and Swap
		vector& operator=(vector other) noexcept {
			this->swap(other);
			return *this;
		}

		// Need to check if self-assigning
		// Memory Safety

		void clear() noexcept {
			std::destroy(data, data + currentSize);
			currentSize = 0;
		}

		size_t length() const noexcept {
			return currentSize;
		}

		T& at(size_t i) {
			if (i >= currentSize) throw std::out_of_range("index out of range");
			return data[i];
		}

		const T& at(size_t i) const {
			if (i >= currentSize) throw std::out_of_range("index out of range");
			return data[i];
		}

		void print() const noexcept requires Streamable<T> {
			std::cout << '[';
			for (size_t i = 0; i < currentSize; ++i) {
				std::cout << at(i);
				if (i < currentSize-1) {
					std::cout << ", ";
				}
			}
			std::cout << ']' << std::endl;
		}

		void reserve(size_t newCapacity) {
			if (newCapacity <= currentCapacity) {
				return;
			}

			T* newData = static_cast<T*>(::operator new(newCapacity * sizeof(T)));
			size_t i = 0;
			try {
				for (; i < currentSize; ++i) {
					new (newData + i) T(std::move_if_noexcept(data[i]));
				}
			} catch (...) {
				for (size_t j = 0; j < i; ++j) newData[j].~T();
				::operator delete(newData);
				throw;
			}

			std::destroy(data, data+currentSize);
			::operator delete(data);

			data = newData;
			currentCapacity = newCapacity;
		}

		void push_back(const T& x) {
			if (currentSize >= currentCapacity) {
				reserve(currentCapacity == 0 ? 1 :currentCapacity*2);
			}
			new (data + currentSize) T(x);
			currentSize++;
		}

		void push_back(T&& value) {
			if (currentSize == currentCapacity) {
				reserve(currentCapacity == 0 ? 1 : currentCapacity * 2);
			}
			new (data + currentSize) T(std::move(value));
			currentSize++;
		}

		// T&& is forwarding reference
		// std::forward keeps the args as they are (lv to lv, rv to rv)
		template <class... Args>
		void emplace_back(Args&&... args) {
			if (currentSize == currentCapacity) {
				reserve(currentCapacity == 0 ? 1 : currentCapacity * 2);
			}

			new (data + currentSize) T(std::forward<Args>(args)...);

			currentSize++;
		}

		void remove(size_t t) {
			if (t >= currentSize) {
				throw std::out_of_range("index out of range");
			}
			for (size_t i = t; i < currentSize - 1; ++i) {
				data[i] = std::move(data[i + 1]);
			}
			data[currentSize-1].~T();
			--currentSize;
		}

		void insert(size_t i, const T& x) {
			if (i > currentSize) {
				throw std::out_of_range("index out of range");
			}
			if (currentSize == currentCapacity) {
				reserve(currentCapacity == 0 ? 1 : currentCapacity * 2);
			}
			if (i == currentSize) {
				new (data + currentSize) T(x);
			} else {
				new (data + currentSize) T(std::move(data[currentSize - 1]));

				for (size_t j = currentSize - 1; j > i; --j) {
					data[j] = std::move(data[j - 1]);
				}

				data[i] = x;
			}

			currentSize++;
		}

		template <class... Args>
		void emplace(size_t i, Args&&... args) {
			if (i > currentSize) {
				throw std::out_of_range("index out of range");
			}
			if (currentSize == currentCapacity) {
				reserve(currentCapacity == 0 ? 1 : currentCapacity * 2);
			}
			if (i == currentSize) {
				new (data + currentSize) T(std::forward<Args>(args)...);
			} else {
				new (data + currentSize) T(std::move(data[currentSize - 1]));

				for (size_t j = currentSize - 1; j > i; --j) {
					data[j] = std::move(data[j - 1]);
				}

				data[i] = T(std::forward<Args>(args)...);
			}

			currentSize++;
		}

		void pop_back() {
			if (currentSize == 0) {
				throw std::out_of_range("index out of range");
			}
			data[currentSize-1].~T();
			currentSize--;
		}

		void pop_front() {
			remove(0);
		}

		void push_front(const T& x) {
			insert(0, x);
		}

		template <class... Args>
		void emplace_front(Args... args) {
			emplace(0, std::forward<Args>(args)...);
		}

		std::optional<size_t> search(const T& x) const {
			for (size_t i = 0; i < currentSize; ++i) {
				if (data[i] == x) {
					return i;
				}
			}
			return std::nullopt;
		}

		iterator begin() noexcept {
			return data;
		}

		iterator end() noexcept {
			return data + currentSize;
		}

		const_iterator begin() const noexcept {
			return data;
		}

		const_iterator end() const noexcept {
			return data + currentSize;
		}
	};
}

#endif //MY_STL_VECTOR_H