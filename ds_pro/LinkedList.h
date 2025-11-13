//
// Created by Chenluo Deng on 11/13/25.
//

#ifndef DS_LINKEDLIST_H
#define DS_LINKEDLIST_H
#include <iostream>
#include <memory>
#include "../concepts.h"

namespace MySTL {
	namespace DS {
		template<class T>
		requires (MySTL::Copy<T> || MySTL::Move<T>)
		class LinkedList {
		public:
			struct Node {
				int id;
				T data;
				std::unique_ptr<Node> next;
			};
			std::unique_ptr<Node> head;
			int size = 0;
			LinkedList() : head(nullptr) {}
			explicit LinkedList(T data) : head(std::make_unique<Node>(0, std::move(data), nullptr)), size(1) {}
			LinkedList(std::initializer_list<T> init) : LinkedList() {
				for (auto i : init) {
					push_back(i);
				}
			}

			~LinkedList() {

			}

			void push_back(T data);

			bool find(const T data) const;

			void removeAt(int id);
		};

		template<typename T>
		requires (MySTL::Copy<T> || MySTL::Move<T>)
		void LinkedList<T>::removeAt(int id) {
			if (!head) {
				return;
			}

			if (head->id == id) {
				head = std::move(head->next);
				size--;
				return;
			}

			Node *prevNode = head.get();
			while (prevNode->next != nullptr && prevNode->next->id != id) {
				prevNode = prevNode->next.get();
			}

			if (prevNode->next != nullptr) {
				prevNode->next = std::move(prevNode->next->next);
				size--;
			}
		}

		template<typename T>
		requires (MySTL::Copy<T> || MySTL::Move<T>)
		void LinkedList<T>::push_back(T data) {
			// Pass-by-value (T data) is fine, but std::move it into the constructor
			auto newNode = std::make_unique<Node>(size++, std::move(data), nullptr);

			if (!head) {
				// Handle case where list is empty
				head = std::move(newNode);
				return;
			}

			auto currentNode = head.get();
			while (currentNode->next != nullptr) {
				currentNode = currentNode->next.get();
			}
			currentNode->next = std::move(newNode);
		}

		template<typename T>
		requires (MySTL::Copy<T> || MySTL::Move<T>)
		bool LinkedList<T>::find(const T data) const {
			auto currentNode = head.get();
			while (currentNode != nullptr) {
				if (currentNode->data == data) {
					return true;
				}
				currentNode = currentNode->next.get();
			}
			return false;
		}
	} // DS
}

#endif //DS_LINKEDLIST_H