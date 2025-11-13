#include <iostream>
#include <string>
#include "ds_pro/LinkedList.h"
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

TEST(LinkedListTest, PrintAndStreamOperator) {
	MySTL::DS::LinkedList<std::string> list = {"A", "B", "C"};
	testing::internal::CaptureStdout();
	list.print();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("List (size 3):"), std::string::npos);
}