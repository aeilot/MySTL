//
// Created by Chenluo Deng on 11/14/25.
//

#ifndef MY_STL_CONTAINER_H
#define MY_STL_CONTAINER_H
#include "concepts.h"

namespace MySTL {
	namespace DS {
		/**
		 * @brief A fixed-size array implementation that supports copy and move semantics.
		 *
		 * @tparam T The type of elements stored in the array. Must satisfy either Copy or Move concepts.
		 * @tparam N The size of the array.
		 */
		template<class T, size_t N>
			requires (MySTL::Copy<T> || MySTL::Move<T>)
		class Array {
			T *data; ///< Pointer to the dynamically allocated array of elements.
		public:
			/**
			 * @brief Destructor. Releases the allocated memory.
			 */
			~Array() {
				delete[] data;
			}

			/**
			 * @brief Default constructor. Allocates memory for the array.
			 */
			Array() {
				data = new T[N];
			}

			Array(Array &rhs) noexcept {
				data = new T[N];
				for (size_t i = 0; i < N; i++) {
					this->data[i] = rhs.data[i];
				}
			}

			Array(Array &&rhs) noexcept : data(rhs.data) {
				rhs.data = nullptr;
			}

			/**
			 * @brief Returns the size of the array.
			 *
			 * @return The size of the array.
			 */
			size_t size() const {
				return N;
			}

			/**
			 * @brief Accesses the element at the specified index.
			 *
			 * @param i The index of the element to access.
			 * @return A reference to the element at the specified index.
			 * @throws std::out_of_range If the index is out of bounds.
			 */
			T &operator[](size_t i) {
				if (i >= N) {
					throw std::out_of_range("Array index out of range");
				}
				return data[i];
			}

			const T& operator[](size_t index) const {
				if (index < 0 || index >= N) {
					throw std::out_of_range("Index out of range");
				}
				return this->data[index];
			}

			Array& operator=(const Array &rhs) {
				if (this == &rhs) {
					return *this;
				}
				T* new_data = new T[N];
				for (int i = 0; i < N; i++) {
					new_data[i] = rhs.data[i];
				}
				delete[] this->data;
				this->data = new_data;
				return *this;
			}

			Array& operator=(Array &&rhs) {
				if (this == &rhs) {
					return *this;
				}
				delete[] this->data;
				this->data = rhs.data;
				rhs.data = nullptr;
				return *this;
			}

			/**
			 * @brief Applies a function to a range of elements in the array.
			 *
			 * @param from The starting index of the range (inclusive).
			 * @param to The ending index of the range (exclusive).
			 * @param f The function to apply to each element in the range.
			 * @throws std::out_of_range If the range is invalid.
			 */
			void map(size_t from, size_t to, void (*f)(T &)) {
				if (from > N || to > N || from > to) {
					throw std::out_of_range("Index out of range");
				}
				for (size_t i = from; i < to; i++) {
					f(data[i]);
				}
			}

			/**
			 * @brief Applies a function to all elements in the array.
			 *
			 * @param f The function to apply to each element.
			 */
			void map(void (*f)(T &)) {
				map(0, N, f);
			}
		};
	} // DS
} // MySTL

#endif //MY_STL_CONTAINER_H
