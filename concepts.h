//
// Created by Chenluo Deng on 11/13/25.
//

#ifndef MY_STL_CONCEPTS_H
#define MY_STL_CONCEPTS_H

#include <concepts>
#include <iosfwd>
#include <iostream>

namespace MySTL {

 /**
  * @brief Concept to check if a type is copy constructible.
  *
  * @tparam T The type to check.
  */
 template<class T>
 concept Copy = std::copy_constructible<T>;

 /**
  * @brief Concept to check if a type is move constructible.
  *
  * @tparam T The type to check.
  */
 template<class T>
 concept Move = std::move_constructible<T>;

 /**
  * @brief Concept to check if a type supports equality comparison.
  *
  * @tparam T The type to check.
  */
 template<typename T>
 concept Eq = requires(T a, T b) {
  { a == b }; ///< Checks if the type supports `==` operator.
  { a != b }; ///< Checks if the type supports `!=` operator.
 };

 /**
  * @brief Concept to check if a type supports partial ordering.
  *
  * @tparam T The type to check.
  */
 template<typename T>
 concept PartialEq = requires(T a, T b) {
  { a < b };  ///< Checks if the type supports `<` operator.
  { a > b };  ///< Checks if the type supports `>` operator.
  { a <= b }; ///< Checks if the type supports `<=` operator.
  { a >= b }; ///< Checks if the type supports `>=` operator.
 };

 /**
  * @brief Concept to check if a type supports both equality and partial ordering.
  *
  * @tparam T The type to check.
  */
 template<typename T>
 concept Ord = requires(T a, T b) {
  requires PartialEq<T>; ///< Requires the type to satisfy PartialEq.
  requires Eq<T>;        ///< Requires the type to satisfy Eq.
 };

 /**
  * @brief Concept to check if a type can be converted to another type.
  *
  * @tparam T The source type.
  * @tparam U The target type.
  */
 template<typename T, typename U>
 concept ConvertibleTo = requires(T a) {
  { static_cast<U>(a) } -> std::convertible_to<U>; ///< Checks if the type can be cast to the target type.
 };

 /**
  * @brief Concept to check if a type is printable to an output stream.
  *
  * @tparam T The type to check.
  */
 template<typename T>
 concept Printable = requires(T a) {
  { std::cout << a } -> std::same_as<std::ostream&>; ///< Checks if the type supports streaming to `std::cout`.
 };

 namespace ops {

  /**
   * @brief Concept to check if a type supports addition.
   *
   * @tparam T The type to check.
   */
  template<typename T>
  concept Add = requires(T a, T b) {
   { a + b }; ///< Checks if the type supports `+` operator.
  };

  /**
   * @brief Concept to check if a type supports subtraction.
   *
   * @tparam T The type to check.
   */
  template<typename T>
  concept Sub = requires(T a, T b) {
   { a - b }; ///< Checks if the type supports `-` operator.
  };

  /**
   * @brief Concept to check if a type supports multiplication.
   *
   * @tparam T The type to check.
   */
  template<typename T>
  concept Mul = requires(T a, T b) {
   { a * b }; ///< Checks if the type supports `*` operator.
  };

  /**
   * @brief Concept to check if a type supports division.
   *
   * @tparam T The type to check.
   */
  template<typename T>
  concept Div = requires(T a, T b) {
   { a / b }; ///< Checks if the type supports `/` operator.
  };

 }

}

#endif //MY_STL_CONCEPTS_H
