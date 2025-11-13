//
// Created by Chenluo Deng on 11/13/25.
//

#ifndef MY_STL_CONCEPTS_H
#define MY_STL_CONCEPTS_H

#include <concepts>
#include <iosfwd>
#include <iostream>

namespace MySTL {
	template<class T>
	concept Copy = std::copy_constructible<T>;

	template<class T>
	concept Move = std::move_constructible<T>;

	template<typename T>
	concept Eq = requires(T a, T b){
		{ a == b };
		{ a != b };
	};

	template<typename T>
	concept PartialEq = requires(T a, T b){
		{ a < b };
		{ a > b };
		{ a <= b };
		{ a >= b };
	};

	template<typename T>
	concept Ord = requires(T a, T b){
		requires PartialEq<T>;
		requires Eq<T>;
	};

	template<typename T, typename U>
	concept ConvertibleTo = requires(T a){
		{ static_cast<U>(a) } -> std::convertible_to<U>;
	};

	template<typename T>
	concept Printable = requires(T a){
		{ std::cout << a } -> std::same_as<std::ostream&>;
	};

	namespace ops {
		template<typename T>
		concept Add = requires(T a, T b)
		{
			{ a + b };
		};

		template<typename T>
		concept Sub = requires(T a, T b)
		{
			{a - b};
		};

		template<typename T>
		concept Mul = requires(T a, T b)
		{
			{a * b};
		};

		template<typename T>
		concept Div = requires(T a, T b)
		{
			{a / b};
		};
	}
}

#endif //MY_STL_CONCEPTS_H