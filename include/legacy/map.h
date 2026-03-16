//
// Created by Chenluo Deng on 3/2/26.
//

#ifndef MY_STL_MAP_H
#define MY_STL_MAP_H
#include <memory>
#include <optional>

namespace DS {
	const int capacity = 10007;

	template <typename T>
	class Map {
	private:
		struct Node {
			int key;
			T value;
			Node* next;
		};

	public:
		unsigned int f(int k) const {
			unsigned int x = static_cast<unsigned int>(k);
			x = ((x >> 16) ^ x) * 0x45d9f3b;
			x = ((x >> 16) ^ x) * 0x45d9f3b;
			x = (x >> 16) ^ x;
			return x % capacity;
		}

		Node** map;

		explicit Map() {
			map = new Node*[capacity];
			for (int i = 0; i < capacity; i++) {
				map[i] = nullptr;
			}
		}

		std::optional<T> find(int k) {
			int fk = f(k);
			if (map[fk]==nullptr) {
				return std::nullopt;
			}
			Node* head = map[fk];
			while (head != nullptr) {
				if (head->key == k) {
					return head->value;
				}
				head = head->next;
			}
			return std::nullopt;
		}

		void write(int k, T v) {
			int fk = f(k);
			Node* head = map[fk];
			while (head != nullptr) {
				if (head->key == k) {
					head->value = v;
					return;
				}
				head = head->next;
			}
			Node* n = new Node();
			n->key = k;
			n->value = v;
			n->next = map[fk];
			map[fk] = n;
		}
	};
}

#endif //MY_STL_MAP_H