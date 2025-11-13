//
// Created by Chenluo Deng on 11/13/25.
//

#ifndef DS_LINKEDLIST_H
#define DS_LINKEDLIST_H
#include <iostream>
#include <memory>

namespace DS {
	template<class T>
	class LinkedList {
		struct Node {
			int id;
			T data;
			std::unique_ptr<Node> next;
		};
	public:
		std::unique_ptr<Node> head;
		int size = 0;
		LinkedList() : head(nullptr) {}
		explicit LinkedList(T data) : head(std::make_unique<Node>(0, std::move(data), nullptr)), size(1) {}
		LinkedList(std::initializer_list<T> init) : LinkedList() {
			for (auto i : init) {
				push_back(i);
			}
		}

		void push_back(T data) {
			auto newNode = std::make_unique<Node>(size++,data, nullptr);

			if (!head) { // Handle case where list is empty
				head = std::move(newNode);
				return;
			}

			auto currentNode = head.get();
			while (currentNode->next != nullptr) {
				currentNode = currentNode->next.get();
			}
			currentNode->next = std::move(newNode);
		}

		bool find(const T data) const {
			auto currentNode = head.get();
			while (currentNode != nullptr) {
				if (currentNode->data == data) {
					return true;
				}
				currentNode = currentNode->next.get();
			}
			return false;
		}

		void removeAt(int id) {
			if (!head) {
				return;
			}

			if (head->id == id) {
				head = std::move(head->next);
				size--;
				return;
			}

			Node* prevNode = head.get();
			while (prevNode->next != nullptr && prevNode->next->id != id) {
				prevNode = prevNode->next.get();
			}

			if (prevNode->next != nullptr) {
				prevNode->next = std::move(prevNode->next->next);
				size--;
			}
		}

		void print() const {
			Node* currentNode = head.get();
			std::cout << "List (size " << size << "): ";
			while (currentNode != nullptr) {
				std::cout << "[" << currentNode->id << ":" << currentNode->data << "] -> ";
				currentNode = currentNode->next.get();
			}
			std::cout << "nullptr" << std::endl;
		}
	};
} // DS

#endif //DS_LINKEDLIST_H