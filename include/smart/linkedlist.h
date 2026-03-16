//
// Created by Chenluo Deng on 3/9/26.
//

#ifndef MY_STL_LINKLIST_H
#define MY_STL_LINKLIST_H
#include <iostream>

namespace DS {
	template <typename T>
	class LinkedList {
		private:
		struct Node {
			T value;
			std::unique_ptr<Node> next;

			Node(const T& value) : value(value), next(nullptr) {}
			Node(T&& value) : value(std::move(value)), next(nullptr) {}
			template<typename... Args>
			Node(Args&&... args) : value(std::forward<Args>(args)...), next(nullptr) {}
		};

		std::unique_ptr<Node> head;

		void insert_after(Node* prev, std::unique_ptr<Node> node) {
			if (prev == nullptr) {
				head = std::move(node);
			} else {
				node->next = std::move(prev->next);
				prev->next = std::move(node);
			}
		}

		void remove_after(Node* node) {
			if (node == nullptr) {
				throw std::out_of_range("node is null");
			}
			if (node->next == nullptr) {
				throw std::out_of_range("node next is null");
			}
			node->next = std::move(node->next->next);
		}

		Node* get(int id) { // Starting from zero
			int i = 0;
			Node * curr = head.get();
			while (curr != nullptr) {
				if (i == id) {
					return curr;
				}
				curr = curr->next.get();
				i++;
			}
			return nullptr;
		}

		public:
		LinkedList() = default;
		LinkedList(std::initializer_list<T> list) {
			for (auto i = std::rbegin(list); i != std::rend(list); i++) {
				push_front(*i);
			}
		}
		~LinkedList() {
			while (head) {
				head = std::move(head->next);
			}
		}

		void push_front(const T& v) {
			auto new_node = std::make_unique<Node>(v);
			if (head == nullptr) {
				head = std::move(new_node);
			} else {
				new_node->next = std::move(head);
				head = std::move(new_node);
			}
		}

		void push_front(T&& v) noexcept {
			auto new_node = std::make_unique<Node>(std::move(v));
			if (head == nullptr) {
				head = std::move(new_node);
			} else {
				new_node->next = std::move(head);
				head = std::move(new_node);
			}
		}

		void push_back(const T& v) {
			auto new_node = std::make_unique<Node>(v);
			if (head == nullptr) {
				head = std::move(new_node);
				return;
			}
			Node* curr = head.get();
			while (curr->next != nullptr) {
				curr = curr->next.get();
			}
			curr->next = std::move(new_node);
		}

		void push_back(T&& v) noexcept {
			auto new_node = std::make_unique<Node>(std::move(v));
			if (head == nullptr) {
				head = std::move(new_node);
				return;
			}
			Node* curr = head.get();
			while (curr->next != nullptr) {
				curr = curr->next.get();
			}
			curr->next = std::move(new_node);
		}

		template<class... Args>
		void emplace_front(Args&&... args) {
			auto new_node = std::make_unique<Node>(std::forward<Args>(args)...);
			if (head == nullptr) {
				head = std::move(new_node);
			} else {
				new_node->next = std::move(head);
				head = std::move(new_node);
			}
		}

		template<class... Args>
		void emplace_back(Args&&... args) {
			auto new_node = std::make_unique<Node>(std::forward<Args>(args)...);
			if (head == nullptr) {
				head = std::move(new_node);
				return;
			}
			Node* curr = head.get();
			while (curr->next != nullptr) {
				curr = curr->next.get();
			}
			curr->next = std::move(new_node);
		}

		void erase_after(int id) {
			Node* node = get(id);
			if (node == nullptr) {
				throw std::out_of_range("node is null");
			}
			remove_after(node);
		}

		void insert_after(int id, T val) {
			auto new_node = std::make_unique<Node>(val);
			Node* node = get(id);
			if (node == nullptr) {
				throw std::out_of_range("node is null");
			}
			insert_after(node, std::move(new_node));
		}

		template<class... Args>
		void emplace_after(int id, Args&&... args) {
			auto new_node = std::make_unique<Node>(std::forward<Args>(args)...);
			Node *node = get(id);
			if (node == nullptr) {
				throw std::out_of_range("node is null");
			}
			insert_after(node, std::move(new_node));
		}

		std::optional<size_t> search(T v) const {
			Node * curr = head.get();
			size_t i = 0;
			while (curr != nullptr) {
				if (curr->value == v) {
					return std::optional<size_t>(i);
				}
				i++;
				curr = curr->next.get();
			}
			return std::nullopt;
		}

		size_t size() const {
			size_t sz = 0;
			Node * curr = head.get();
			while (curr != nullptr) {
				sz++;
				curr = curr->next.get();
			}
			return sz;
		}


	};

}

#endif //MY_STL_LINKLIST_H