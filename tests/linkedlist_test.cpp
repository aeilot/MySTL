#include <gtest/gtest.h>

#include "include/smart/linkedlist.h"

using namespace DS;

class LinkedListTest : public ::testing::Test {
protected:
	LinkedList<int> empty_list;
	LinkedList<int> list_with_data{10, 20, 30};
};

TEST_F(LinkedListTest, ConstructorAndSize) {
	EXPECT_EQ(empty_list.size(), 0);
	EXPECT_EQ(list_with_data.size(), 3);
}

TEST_F(LinkedListTest, PushFront) {
	empty_list.push_front(1);
	empty_list.emplace_front(2);
	EXPECT_EQ(empty_list.size(), 2);

	auto idx = empty_list.search(2);
	EXPECT_TRUE(idx.has_value());
	EXPECT_EQ(idx.value(), 0);
}

TEST_F(LinkedListTest, PushBack) {
	empty_list.push_back(100);
	empty_list.push_back(200);
	EXPECT_EQ(empty_list.size(), 2);

	EXPECT_EQ(empty_list.search(100).value(), 0);
	EXPECT_EQ(empty_list.search(200).value(), 1);
}

TEST_F(LinkedListTest, EmplaceAfter) {
	list_with_data.emplace_after(0, 15);

	EXPECT_EQ(list_with_data.size(), 4);
	EXPECT_EQ(list_with_data.search(15).value(), 1);

	EXPECT_THROW(list_with_data.emplace_after(10, 999), std::out_of_range);
}

TEST_F(LinkedListTest, EraseAfter) {
	list_with_data.erase_after(0);

	EXPECT_EQ(list_with_data.size(), 2);
	EXPECT_FALSE(list_with_data.search(20).has_value());
	EXPECT_EQ(list_with_data.search(30).value(), 1);
}

TEST_F(LinkedListTest, SearchFunctionality) {
	auto result = list_with_data.search(20);
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(result.value(), 1);

	auto fail_result = list_with_data.search(999);
	EXPECT_FALSE(fail_result.has_value());
}
