#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "include/smart/vector.h"

using DS::vector;

TEST(VectorTest, DefaultConstructor) {
	vector<int> v;
	EXPECT_EQ(v.size(), 0);
	EXPECT_EQ(v.capacity(), 0);
	EXPECT_EQ(v.length(), 0);
}

TEST(VectorTest, CapacityConstructor) {
	vector<int> v(8);
	EXPECT_EQ(v.size(), 0);
	EXPECT_EQ(v.capacity(), 8);
}

TEST(VectorTest, InitializerListConstructor) {
	vector<int> v{1, 2, 3};
	EXPECT_EQ(v.size(), 3);
	EXPECT_GE(v.capacity(), 3);
	EXPECT_EQ(v.at(0), 1);
	EXPECT_EQ(v.at(1), 2);
	EXPECT_EQ(v.at(2), 3);
}

TEST(VectorTest, PushBackLValue) {
	vector<int> v;
	int x = 42;
	v.push_back(x);

	ASSERT_EQ(v.size(), 1);
	EXPECT_EQ(v.at(0), 42);
}

TEST(VectorTest, PushBackRValue) {
	vector<std::string> v;
	v.push_back(std::string("hello"));

	ASSERT_EQ(v.size(), 1);
	EXPECT_EQ(v.at(0), "hello");
}

TEST(VectorTest, EmplaceBack) {
	vector<std::pair<int, std::string>> v;
	v.emplace_back(1, "one");
	v.emplace_back(2, "two");

	ASSERT_EQ(v.size(), 2);
	EXPECT_EQ(v.at(0).first, 1);
	EXPECT_EQ(v.at(0).second, "one");
	EXPECT_EQ(v.at(1).first, 2);
	EXPECT_EQ(v.at(1).second, "two");
}

TEST(VectorTest, ReservePreservesElements) {
	vector<int> v{1, 2, 3};
	v.reserve(16);

	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v.capacity(), 16);
	EXPECT_EQ(v.at(0), 1);
	EXPECT_EQ(v.at(1), 2);
	EXPECT_EQ(v.at(2), 3);
}

TEST(VectorTest, CopyConstructorMakesDeepCopy) {
	vector<int> a{1, 2, 3};
	vector<int> b(a);

	ASSERT_EQ(b.size(), 3);
	EXPECT_EQ(b.at(0), 1);
	EXPECT_EQ(b.at(1), 2);
	EXPECT_EQ(b.at(2), 3);

	b.at(1) = 99;
	EXPECT_EQ(a.at(1), 2);
	EXPECT_EQ(b.at(1), 99);
}

TEST(VectorTest, MoveConstructorTransfersOwnership) {
	vector<int> a{1, 2, 3};
	vector<int> b(std::move(a));

	ASSERT_EQ(b.size(), 3);
	EXPECT_EQ(b.at(0), 1);
	EXPECT_EQ(b.at(1), 2);
	EXPECT_EQ(b.at(2), 3);

	EXPECT_EQ(a.size(), 0);
	EXPECT_EQ(a.capacity(), 0);
}

TEST(VectorTest, CopyAssignment) {
	vector<int> a{1, 2, 3};
	vector<int> b;
	b = a;

	ASSERT_EQ(b.size(), 3);
	EXPECT_EQ(b.at(0), 1);
	EXPECT_EQ(b.at(1), 2);
	EXPECT_EQ(b.at(2), 3);

	b.at(0) = 10;
	EXPECT_EQ(a.at(0), 1);
	EXPECT_EQ(b.at(0), 10);
}

TEST(VectorTest, MoveAssignment) {
	vector<std::string> a{"a", "b", "c"};
	vector<std::string> b;
	b = std::move(a);

	ASSERT_EQ(b.size(), 3);
	EXPECT_EQ(b.at(0), "a");
	EXPECT_EQ(b.at(1), "b");
	EXPECT_EQ(b.at(2), "c");

	EXPECT_EQ(a.size(), 0);
	EXPECT_EQ(a.capacity(), 0);
}

TEST(VectorTest, InsertAtBeginning) {
	vector<int> v{2, 3};
	v.insert(0, 1);

	ASSERT_EQ(v.size(), 3);
	EXPECT_EQ(v.at(0), 1);
	EXPECT_EQ(v.at(1), 2);
	EXPECT_EQ(v.at(2), 3);
}

TEST(VectorTest, InsertAtMiddle) {
	vector<int> v{1, 3};
	v.insert(1, 2);

	ASSERT_EQ(v.size(), 3);
	EXPECT_EQ(v.at(0), 1);
	EXPECT_EQ(v.at(1), 2);
	EXPECT_EQ(v.at(2), 3);
}

TEST(VectorTest, InsertAtEnd) {
	vector<int> v{1, 2};
	v.insert(2, 3);

	ASSERT_EQ(v.size(), 3);
	EXPECT_EQ(v.at(0), 1);
	EXPECT_EQ(v.at(1), 2);
	EXPECT_EQ(v.at(2), 3);
}

TEST(VectorTest, EmplaceAtMiddle) {
	vector<std::pair<int, std::string>> v;
	v.emplace_back(1, "one");
	v.emplace_back(3, "three");
	v.emplace(1, 2, "two");

	ASSERT_EQ(v.size(), 3);
	EXPECT_EQ(v.at(0).first, 1);
	EXPECT_EQ(v.at(1).first, 2);
	EXPECT_EQ(v.at(2).first, 3);
	EXPECT_EQ(v.at(1).second, "two");
}

TEST(VectorTest, RemoveMiddle) {
	vector<int> v{1, 2, 3, 4};
	v.remove(1);

	ASSERT_EQ(v.size(), 3);
	EXPECT_EQ(v.at(0), 1);
	EXPECT_EQ(v.at(1), 3);
	EXPECT_EQ(v.at(2), 4);
}

TEST(VectorTest, PopBack) {
	vector<int> v{1, 2, 3};
	v.pop_back();

	ASSERT_EQ(v.size(), 2);
	EXPECT_EQ(v.at(0), 1);
	EXPECT_EQ(v.at(1), 2);
}

TEST(VectorTest, PopFront) {
	vector<int> v{1, 2, 3};
	v.pop_front();

	ASSERT_EQ(v.size(), 2);
	EXPECT_EQ(v.at(0), 2);
	EXPECT_EQ(v.at(1), 3);
}

TEST(VectorTest, PushFront) {
	vector<int> v{2, 3};
	v.push_front(1);

	ASSERT_EQ(v.size(), 3);
	EXPECT_EQ(v.at(0), 1);
	EXPECT_EQ(v.at(1), 2);
	EXPECT_EQ(v.at(2), 3);
}

TEST(VectorTest, SearchFound) {
	vector<int> v{5, 6, 7};
	auto pos = v.search(6);

	ASSERT_TRUE(pos.has_value());
	EXPECT_EQ(*pos, 1u);
}

TEST(VectorTest, SearchNotFound) {
	vector<int> v{5, 6, 7};
	auto pos = v.search(10);

	EXPECT_FALSE(pos.has_value());
}

TEST(VectorTest, Clear) {
	vector<int> v{1, 2, 3};
	v.clear();

	EXPECT_EQ(v.size(), 0);
	EXPECT_GE(v.capacity(), 3);
}

TEST(VectorTest, AtThrowsOnInvalidIndex) {
	vector<int> v{1, 2, 3};
	EXPECT_THROW(v.at(3), std::out_of_range);
}

TEST(VectorTest, PopBackThrowsOnEmptyVector) {
	vector<int> v;
	EXPECT_THROW(v.pop_back(), std::out_of_range);
}

TEST(VectorTest, RemoveThrowsOnInvalidIndex) {
	vector<int> v{1, 2, 3};
	EXPECT_THROW(v.remove(3), std::out_of_range);
}

TEST(VectorTest, InsertThrowsOnInvalidIndex) {
	vector<int> v{1, 2, 3};
	EXPECT_THROW(v.insert(4, 10), std::out_of_range);
}
