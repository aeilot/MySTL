//
// Created by Chenluo Deng on 11/13/25.
//

#ifndef DS_LINKEDLIST_H
#define DS_LINKEDLIST_H
#include <iostream>
#include <memory>
#include "concepts.h"

namespace MySTL {
	namespace DS {
		/**
		 * @brief A singly linked list implementation that supports copy and move semantics.
		 *
		 * @tparam T The type of elements stored in the linked list. Must satisfy either Copy or Move concepts.
		 */
		template<class T>
			requires (MySTL::Copy<T> || MySTL::Move<T>)
		class LinkedList {
		public:
			/**
			 * @brief A node in the linked list.
			 */
			struct Node {
				int id; ///< The unique identifier of the node.
				T data; ///< The data stored in the node.
				std::unique_ptr<Node> next; ///< Pointer to the next node in the list.
			};

			std::unique_ptr<Node> head; ///< Pointer to the head node of the list.
			size_t size = 0; ///< The current size of the linked list.

			/**
			 * @brief Default constructor. Initializes an empty linked list.
			 */
			LinkedList() : head(nullptr) {
			}

			/**
			 * @brief Constructs a linked list with a single element.
			 *
			 * @param data The data to initialize the linked list with.
			 */
			explicit LinkedList(T data) : head(std::make_unique<Node>(0, std::move(data), nullptr)), size(1) {
			}

			/**
			 * @brief Constructs a linked list from an initializer list.
			 *
			 * @param init The initializer list to construct the linked list from.
			 */
			LinkedList(std::initializer_list<T> init) : LinkedList() {
				for (auto i: init) {
					push_back(i);
				}
			}

			/**
			 * @brief Destructor. Releases all allocated memory.
			 */
			~LinkedList() {
			}

			/**
			 * @brief Adds an element to the end of the linked list.
			 *
			 * @param data The data to add to the list.
			 */
			void push_back(T data);

			/**
			 * @brief Checks if the linked list contains the specified element.
			 *
			 * @param data The data to search for.
			 * @return True if the element is found, false otherwise.
			 */
			bool find(const T data) const;

			/**
			 * @brief Removes the node with the specified id from the linked list.
			 *
			 * @param id The id of the node to remove.
			 */
			void removeAt(int id);
		};

		/**
		 * @brief Removes the node with the specified id from the linked list.
		 *
		 * @tparam T The type of elements stored in the linked list.
		 * @param id The id of the node to remove.
		 */
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

		/**
		 * @brief Adds an element to the end of the linked list.
		 *
		 * @tparam T The type of elements stored in the linked list.
		 * @param data The data to add to the list.
		 */
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

		/**
		 * @brief Checks if the linked list contains the specified element.
		 *
		 * @tparam T The type of elements stored in the linked list.
		 * @param data The data to search for.
		 * @return True if the element is found, false otherwise.
		 */
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
