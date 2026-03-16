#ifndef MY_STL_QUEUE_H
#define MY_STL_QUEUE_H

#include <stdexcept>
#include <algorithm>

namespace DS {
	template<class T>
	class Queue {
	private:
		T* data;
		int capacity;
		int head;
		int tail;
		int count;

		void resize() {
			int new_capacity = (capacity == 0) ? 8 : capacity * 2;
			T* new_data = new T[new_capacity];

			for (int i = 0; i < count; ++i) {
				new_data[i] = std::move(data[(head + i) % capacity]);
			}

			delete[] data;
			data = new_data;
			capacity = new_capacity;
			head = 0;
			tail = count;
		}

	public:
		explicit Queue(int init_capacity = 8)
			: capacity(init_capacity), head(0), tail(0), count(0) {
			data = static_cast<T*>(operator new(init_capacity * sizeof(T)));
		}

		~Queue() {
			while (!empty()) {
				pop();
			}
			operator delete(data);
		}

		void push(const T& item) {
			if (count == capacity) {
				resize();
			}
			data[tail] = item;
			tail = (tail + 1) % capacity;
			count++;
		}

		T pop() {
			if (empty()) {
				throw std::out_of_range("Queue is empty");
			}
			T val = std::move(data[head]);
			head = (head + 1) % capacity;
			count--;
			return val;
		}

		bool empty() const { return count == 0; }
		int size() const { return count; }

		Queue(const Queue&) = delete;
		Queue& operator=(const Queue&) = delete;
	};
}

#endif