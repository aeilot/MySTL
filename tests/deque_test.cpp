#include <gtest/gtest.h>

#include "include/smart/deque.h"

TEST(DequeTests, EmptyOnNewDeque) {
	DS::Deque<int> deque(3);
	EXPECT_TRUE(deque.empty());
}

TEST(DequeTests, PushBackPopFrontIsFifo) {
	DS::Deque<int> deque(3);
	deque.push_back(1);
	deque.push_back(2);
	deque.push_back(3);
	EXPECT_FALSE(deque.empty());
	EXPECT_EQ(deque.pop_front(), 1);
	EXPECT_EQ(deque.pop_front(), 2);
	EXPECT_EQ(deque.pop_front(), 3);
	EXPECT_TRUE(deque.empty());
}

TEST(DequeTests, PushFrontPopBackIsFifoFromFrontSide) {
	DS::Deque<int> deque(3);
	deque.push_front(1);
	deque.push_front(2);
	deque.push_front(3);
	EXPECT_FALSE(deque.empty());
	EXPECT_EQ(deque.pop_back(), 1);
	EXPECT_EQ(deque.pop_back(), 2);
	EXPECT_EQ(deque.pop_back(), 3);
	EXPECT_TRUE(deque.empty());
}

TEST(DequeTests, MixedPushPopRespectsEnds) {
	DS::Deque<int> deque(3);
	deque.push_back(10);
	deque.push_front(20);
	deque.push_back(30);
	EXPECT_EQ(deque.pop_front(), 20);
	EXPECT_EQ(deque.pop_back(), 30);
	EXPECT_EQ(deque.pop_front(), 10);
	EXPECT_TRUE(deque.empty());
}

TEST(DequeTests, PopFrontOnEmptyThrows) {
	DS::Deque<int> deque(3);
	EXPECT_THROW(deque.pop_front(), std::out_of_range);
}

TEST(DequeTests, PopBackOnEmptyThrows) {
	DS::Deque<int> deque(3);
	EXPECT_THROW(deque.pop_back(), std::out_of_range);
}

TEST(DequeTests, GrowsWhenPushingFrontBeyondInitialCapacity) {
	DS::Deque<int> deque(1);
	deque.push_front(1);
	deque.push_front(2);
	deque.push_front(3);
	EXPECT_EQ(deque.pop_front(), 3);
	EXPECT_EQ(deque.pop_front(), 2);
	EXPECT_EQ(deque.pop_front(), 1);
}

TEST(DequeTests, GrowsWhenPushingBackBeyondInitialCapacity) {
	DS::Deque<int> deque(1);
	deque.push_back(1);
	deque.push_back(2);
	deque.push_back(3);
	EXPECT_EQ(deque.pop_front(), 1);
	EXPECT_EQ(deque.pop_front(), 2);
	EXPECT_EQ(deque.pop_front(), 3);
}
