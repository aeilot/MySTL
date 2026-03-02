#ifndef MY_STL_DEQUE_H
#define MY_STL_DEQUE_H

#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace DS {
    template<class T>
    class Deque {
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
        explicit Deque(int init_capacity = 8)
            : capacity(init_capacity), head(0), tail(0), count(0) {
            data = static_cast<T*>(operator new(init_capacity * sizeof(T)));
        }

        ~Deque() {
            while (!empty()) pop_front();
        	operator delete(data);
        }

        Deque(const Deque&) = delete;
        Deque& operator=(const Deque&) = delete;

        void push_back(const T& item) {
            if (count == capacity) resize();
            data[tail] = item;
            tail = (tail + 1) % capacity;
            count++;
        }

        void push_front(const T& item) {
            if (count == capacity) resize();
            head = (head - 1 + capacity) % capacity;
            data[head] = item;
            count++;
        }

        T pop_front() {
            if (empty()) throw std::out_of_range("Deque is empty");
            T val = std::move(data[head]);
            head = (head + 1) % capacity;
            count--;
            return val;
        }

        T pop_back() {
            if (empty()) throw std::out_of_range("Deque is empty");
            tail = (tail - 1 + capacity) % capacity;
            T val = std::move(data[tail]);
            count--;
            return val;
        }

        bool empty() const { return count == 0; }
        int size() const { return count; }
        
        T& operator[](int index) {
            if (index < 0 || index >= count) throw std::out_of_range("Index out of bounds");
            return data[(head + index) % capacity];
        }
    };
}

#endif