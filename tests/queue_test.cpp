#include <gtest/gtest.h>

#include "include/smart/queue.h"

TEST(QueueTests, EmptyOnNewQueue) {
	DS::Queue<int> queue(2);
	EXPECT_TRUE(queue.empty());
}

TEST(QueueTests, PushPopIsFifo) {
	DS::Queue<int> queue(2);
	queue.push(1);
	queue.push(2);
	EXPECT_FALSE(queue.empty());
	EXPECT_EQ(queue.pop(), 1);
	EXPECT_EQ(queue.pop(), 2);
	EXPECT_TRUE(queue.empty());
}

TEST(QueueTests, PopOnEmptyThrows) {
	DS::Queue<int> queue(1);
	EXPECT_THROW(queue.pop(), std::out_of_range);
}

TEST(QueueTests, GrowsBeyondInitialCapacity) {
	DS::Queue<int> queue(1);
	queue.push(10);
	queue.push(20);
	queue.push(30);
	EXPECT_EQ(queue.pop(), 10);
	EXPECT_EQ(queue.pop(), 20);
	EXPECT_EQ(queue.pop(), 30);
}
