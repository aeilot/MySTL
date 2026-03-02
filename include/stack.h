#ifndef MY_STL_STACK_H
#define MY_STL_STACK_H

#include <stdexcept>
#include <algorithm> // 用于 std::move 和 std::copy

namespace DS {
	template<class T>
	class Stack {
	private:
		int capacity;
		T* data;
		int top_ptr;

		void resize() {
			int new_capacity = (capacity == 0) ? 8 : capacity * 2;
			T* new_data = new T[new_capacity];

			for (int i = 0; i < top_ptr; ++i) {
				new_data[i] = std::move(data[i]);
			}

			delete[] data;
			data = new_data;
			capacity = new_capacity;
		}

	public:
		explicit Stack(int init_capacity = 8)
			: capacity(init_capacity), top_ptr(0) {
			data = new T[capacity];
		}

		~Stack() {
			delete[] data;
		}

		Stack(const Stack&) = delete;
		Stack& operator=(const Stack&) = delete;

		void push(const T& item) {
			if (top_ptr == capacity) {
				resize();
			}
			data[top_ptr++] = item;
		}

		void push(T&& item) {
			if (top_ptr == capacity) {
				resize();
			}
			data[top_ptr++] = std::move(item);
		}

		T pop() {
			if (empty()) {
				throw std::out_of_range("Stack is empty");
			}
			return std::move(data[--top_ptr]);
		}

		T& top() {
			if (empty()) throw std::out_of_range("Stack is empty");
			return data[top_ptr - 1];
		}

		bool empty() const {
			return top_ptr == 0;
		}

		int size() const {
			return top_ptr;
		}
	};
}

#endif