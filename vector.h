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
	private:
		int sz;
		T* data;
	public:
		vector() : sz(0), data(nullptr) {}

		void reserve(int sz) {
			this->data = new T[sz];
		}

		vector(int sz) : sz(sz) {
			this->data = new T[sz];
		}

		vector(std::initializer_list<T> init) : sz(init.size()) {
			this->data = new T[init.size()];
			for (int i = 0; i < sz; i++) {
				this->data[i] = *(init.begin() + i);
			}
		}

		vector(const vector&rhs) : sz(rhs.sz) {
			this->data = new T[rhs.sz];
			for (int i = 0; i < rhs.sz; i++) {
				this->data[i] = rhs.data[i];
			}
		}

		vector(const vector&&rhs) noexcept {
			this = move(rhs);
		}

		~vector() {
			delete[] data;
		}

		int size() const {
			return this->sz;
		}

		T& operator[](int index) {
			if (index < 0 || index >= this->sz) {
				throw std::out_of_range("Index out of range");
			}
			return this->data[index];
		}

		void resize(int count) {
			if (count <= sz) {
				this->sz = count;
				return;
			}
			T* newD = new T[count];
			memcpy(newD, data, sizeof(T) * sz);
			delete[] data;
			this->data = newD;
			this->sz = count;
		}

		void map(int from, int to, void(*f)(T&)) {
			if (from < 0 || from >= this->sz || to < 0 || to >= this->sz || from > to) {
				throw std::out_of_range("Index out of range");
			}
			for (int i = from; i < to; i++) {
				f(data[i]);
			}
		}
	};
} // DS

#endif //DS_VECTOR_H