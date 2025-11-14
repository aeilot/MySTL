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
 template <class T>
 requires (MySTL::Copy<T> || MySTL::Move<T>)
 class Vec {
 private:
  int sz; ///< The current size of the vector.
  T* data; ///< Pointer to the dynamically allocated array of elements.

 public:
  /**
   * @brief Default constructor. Initializes an empty vector.
   */
  Vec() : sz(0), data(nullptr) {}

  /**
   * @brief Allocates memory for the specified number of elements.
   *
   * @param sz The number of elements to reserve memory for.
   */
  void reserve(int sz) {
   this->data = new T[sz];
  }

  /**
   * @brief Constructs a vector with the specified size.
   *
   * @param sz The size of the vector.
   */
  Vec(int sz) : sz(sz) {
   this->data = new T[sz];
  }

  /**
   * @brief Constructs a vector from an initializer list.
   *
   * @param init The initializer list to construct the vector from.
   */
  Vec(std::initializer_list<T> init) : sz(init.size()) {
   this->data = new T[init.size()];
   for (int i = 0; i < sz; i++) {
    this->data[i] = *(init.begin() + i);
   }
  }

  /**
   * @brief Copy constructor. Creates a deep copy of the given vector.
   *
   * @param rhs The vector to copy from.
   */
  Vec(const Vec& rhs) : sz(rhs.sz) {
   this->data = new T[rhs.sz];
   for (int i = 0; i < rhs.sz; i++) {
    this->data[i] = rhs.data[i];
   }
  }

  /**
   * @brief Move constructor. Transfers ownership of resources from the given vector.
   *
   * @param rhs The vector to move from.
   */
  Vec(const Vec&& rhs) noexcept {
   this = move(rhs);
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
  int size() const {
   return this->sz;
  }

  /**
   * @brief Accesses the element at the specified index.
   *
   * @param index The index of the element to access.
   * @return A reference to the element at the specified index.
   * @throws std::out_of_range If the index is out of bounds.
   */
  T& operator[](int index) {
   if (index < 0 || index >= this->sz) {
    throw std::out_of_range("Index out of range");
   }
   return this->data[index];
  }

  /**
   * @brief Resizes the vector to the specified size.
   *
   * @param count The new size of the vector.
   */
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

  /**
   * @brief Applies a function to a range of elements in the vector.
   *
   * @param from The starting index of the range (inclusive).
   * @param to The ending index of the range (exclusive).
   * @param f The function to apply to each element in the range.
   * @throws std::out_of_range If the range is invalid.
   */
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
