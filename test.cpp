#include <iostream>
#include <string>
#include "ds_pro/LinkedList.h"
#include "vector.h"
#include "concepts.h"
#include <gtest/gtest.h>


TEST(LinkedListTest, DefaultConstructorAndPushBack) {
	MySTL::DS::LinkedList<std::string> list;
	EXPECT_EQ(list.size, 0);
	list.push_back("Hello");
	list.push_back("World");
	EXPECT_EQ(list.size, 2);
	EXPECT_TRUE(list.find("Hello"));
	EXPECT_TRUE(list.find("World"));
	EXPECT_FALSE(list.find("!"));
}

TEST(LinkedListTest, InitializerListConstructor) {
	MySTL::DS::LinkedList<int> list = {1, 2, 3, 4, 5};
	EXPECT_EQ(list.size, 5);
	for (int i = 1; i <= 5; ++i) {
		EXPECT_TRUE(list.find(i));
	}
	EXPECT_FALSE(list.find(6));
}

TEST(LinkedListTest, RemoveAt) {
	MySTL::DS::LinkedList<int> list = {10, 20, 30, 40, 50};
	EXPECT_EQ(list.size, 5);
	list.removeAt(2); // Remove element with id 2 (data 30)
	EXPECT_EQ(list.size, 4);
	EXPECT_FALSE(list.find(30));
	list.removeAt(0); // Remove head (data 10)
	EXPECT_EQ(list.size, 3);
	EXPECT_FALSE(list.find(10));
	list.removeAt(4); // Remove tail (data 50)
	EXPECT_EQ(list.size, 2);
	EXPECT_FALSE(list.find(50));
	list.removeAt(99); // Non-existent id
	EXPECT_EQ(list.size, 2); // Size should remain unchanged
}

TEST(LinkedListTest, SingleElementConstructor) {
	MySTL::DS::LinkedList<double> list(3.14);
	EXPECT_EQ(list.size, 1);
	EXPECT_TRUE(list.find(3.14));
	list.push_back(6.28);
	EXPECT_EQ(list.size, 2);
	EXPECT_TRUE(list.find(6.28));
}

TEST(LinkedListTest, RemoveFromEmptyList) {
	MySTL::DS::LinkedList<char> list;
	EXPECT_EQ(list.size, 0);
	list.removeAt(0); // Attempt to remove from empty list
	EXPECT_EQ(list.size, 0); // Size should remain unchanged
}
TEST(LinkedListTest, FindInEmptyList) {
	MySTL::DS::LinkedList<int> list;
	EXPECT_EQ(list.size, 0);
	EXPECT_FALSE(list.find(42)); // Searching in empty list should return false
}

TEST(VectorTest, DefaultConstructorAndSize) {
	MySTL::DS::vector<int> vec;
	EXPECT_EQ(vec.size(), 0);
}

TEST(VectorTest, InitializerListConstructor) {
	MySTL::DS::vector<std::string> vec = {"Hello", "World", "!"};
	EXPECT_EQ(vec.size(), 3);
	EXPECT_EQ(vec[0], "Hello");
	EXPECT_EQ(vec[1], "World");
	EXPECT_EQ(vec[2], "!");
}

TEST(VectorTest, CopyConstructor) {
	MySTL::DS::vector<int> vec1 = {1, 2, 3, 4, 5};
	MySTL::DS::vector<int> vec2 = vec1; // Copy constructor
	EXPECT_EQ(vec2.size(), 5);
	for (int i = 0; i < vec2.size(); ++i) {
		EXPECT_EQ(vec2[i], vec1[i]);
	}
}

TEST(VectorTest, ElementAccessOutOfRange) {
	MySTL::DS::vector<int> vec = {10, 20, 30};
	EXPECT_THROW(vec[-1], std::out_of_range);
	EXPECT_THROW(vec[3], std::out_of_range);
}

TEST(VectorTest, MapFunction) {
	MySTL::DS::vector<int> vec = {1, 2, 3, 4, 5};
	auto increment = [](int& x) { x += 1; };
	vec.map(1, 4, increment); // Increment elements at indices 1, 2, 3
	EXPECT_EQ(vec[0], 1);
	EXPECT_EQ(vec[1], 3);
	EXPECT_EQ(vec[2], 4);
	EXPECT_EQ(vec[3], 5);
	EXPECT_EQ(vec[4], 5);
}

TEST(ConceptTest, CopyConcept) {
	static_assert(MySTL::Copy<int>, "int should satisfy Copy concept");
	static_assert(MySTL::Copy<std::string>, "std::string should satisfy Copy concept");
	struct NonCopyable {
		NonCopyable() = default;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
	};
	static_assert(!MySTL::Copy<NonCopyable>, "NonCopyable should not satisfy Copy concept");
}

TEST(ConceptTest, MoveConcept) {
	static_assert(MySTL::Move<std::unique_ptr<int>>, "std::unique_ptr<int> should satisfy Move concept");
	struct NonMovable {
		NonMovable() = default;
		NonMovable(NonMovable&&) = delete;
		NonMovable& operator=(NonMovable&&) = delete;
	};
	static_assert(!MySTL::Move<NonMovable>, "NonMovable should not satisfy Move concept");
}

TEST(ConceptTest, OrderedConcept) {
	static_assert(MySTL::Ord<int>, "int should satisfy Ordered concept");
	static_assert(MySTL::Ord<std::string>, "std::string should satisfy Ordered concept");
	struct NonOrdered {
		NonOrdered() = default;
	};
	static_assert(!MySTL::Ord<NonOrdered>, "NonOrdered should not satisfy Ordered concept");
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}