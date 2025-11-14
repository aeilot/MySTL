//
// Created by Chenluo Deng on 11/13/25.
//

#ifndef DS_VECTOR_H
#define DS_VECTOR_H
#include "concepts.h"

namespace MySTL::DS {
	/**
	 * @brief A dynamic array implementation that supports copy and move semantics.
	 *
	 * @tparam T The type of elements stored in the vector. Must satisfy either Copy or Move concepts.
	 */
	template<class T>
		requires (MySTL::Copy<T> || MySTL::Move<T>)
	class Vec {
	private:
		size_t sz; ///< The current size of the vector.
		T *data; ///< Pointer to the dynamically allocated array of elements.

	public:
		/**
		 * @brief Default constructor. Initializes an empty vector.
		 */
		Vec() : sz(0), data(nullptr) {
		}

		/**
		 * @brief Allocates memory for the specified number of elements.
		 *
		 * @param sz The number of elements to reserve memory for.
		 */
		void reserve(size_t sz) {
			this->data = new T[sz];
		}

		/**
		 * @brief Constructs a vector with the specified size.
		 *
		 * @param sz The size of the vector.
		 */
		Vec(size_t sz) : sz(sz) {
			this->data = new T[sz];
		}

		/**
		 * @brief Constructs a vector from an initializer list.
		 *
		 * @param init The initializer list to construct the vector from.
		 */
		Vec(std::initializer_list<T> init) : sz(init.size()) {
			this->data = new T[init.size()];
			for (size_t i = 0; i < sz; i++) {
				this->data[i] = *(init.begin() + i);
			}
		}

		/**
		 * @brief Copy constructor. Creates a deep copy of the given vector.
		 *
		 * @param rhs The vector to copy from.
		 */
		Vec(const Vec &rhs) : sz(rhs.sz) {
			this->data = new T[rhs.sz];
			for (size_t i = 0; i < rhs.sz; i++) {
				this->data[i] = rhs.data[i];
			}
		}

		/**
		 * @brief Move constructor. Transfers ownership of resources from the given vector.
		 *
		 * @param rhs The vector to move from.
		 */
		Vec(Vec&& rhs) noexcept
			: sz(rhs.sz), data(rhs.data)
		{
			rhs.sz = 0;
			rhs.data = nullptr;
		}

		/**
		 * @brief Destructor. Releases the allocated memory.
		 */
		~Vec() {
			delete[] data;
		}

		/**
		 * @brief Returns the current size of the vector.
		 *
		 * @return The size of the vector.
		 */
		size_t size() const {
			return this->sz;
		}

		/**
		 * @brief Accesses the element at the specified index.
		 *
		 * @param index The index of the element to access.
		 * @return A reference to the element at the specified index.
		 * @throws std::out_of_range If the index is out of bounds.
		 */
		T &operator[](size_t index) {
			if (index >= this->sz) {
				throw std::out_of_range("Index out of range");
			}
			return this->data[index];
		}

		const T& operator[](size_t index) const {
			if (index >= this->sz) {
				throw std::out_of_range("Index out of range");
			}
			return this->data[index];
		}

		Vec& operator=(const Vec &rhs) {
			if (this == &rhs) {
				return *this;
			}
			T* new_data = new T[rhs.sz];
			for (int i = 0; i < rhs.sz; i++) {
				new_data[i] = rhs.data[i];
			}
			delete[] this->data;
			this->data = new_data;
			this->sz = rhs.sz;

			return *this;
		}

		Vec& operator=(Vec &&rhs) {
			if (this == &rhs) {
				return *this;
			}
			delete[] this->data;
			this->data = rhs.data;
			this->sz = rhs.sz;
			rhs.data = nullptr;
			rhs.sz = 0;
			return *this;
		}


		/**
		 * @brief Resizes the vector to the specified size.
		 *
		 * @param count The new size of the vector.
		 */
		void resize(size_t count) {
			if (count <= sz) {
				this->sz = count;
				return;
			}
			T *newD = new T[count];
			memcpy(newD, data, sizeof(T) * sz);
			delete[] data;
			this->data = newD;
			this->sz = count;
		}

		/**
		 * @brief Applies a function to a range of elements in the vector.
		 *
		 * @param from The starting index of the range (inclusive).
		 * @param to The ending index of the range (exclusive).
		 * @param f The function to apply to each element in the range.
		 * @throws std::out_of_range If the range is invalid.
		 */
		void map(size_t from, size_t to, void (*f)(T &)) {
			if (from > this->sz || to > this->sz || from > to) {
				throw std::out_of_range("Index out of range");
			}
			for (size_t i = from; i < to; i++) {
				f(data[i]);
			}
		}

		/**
		 * @brief Applies a function to all elements in the vector.
		 *
		 * @param f The function to apply to each element in the range.
		 */
		void map(void (*f)(T &)) {
			map(0, sz, f);
		}
	};
} // DS

#endif //DS_VECTOR_H
