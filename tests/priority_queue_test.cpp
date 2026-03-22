#include <gtest/gtest.h>

#include "include/legacy/priority_queue.h"

TEST(PriorityQueueTest, BasicStatus) {
	PriorityQueue pq;
	EXPECT_TRUE(pq.empty());
	EXPECT_EQ(pq.size(), 0);
}

TEST(PriorityQueueTest, SinglePush) {
	PriorityQueue pq;
	pq.push(10);
	EXPECT_FALSE(pq.empty());
	EXPECT_EQ(pq.size(), 1);
	EXPECT_EQ(pq.front(), 10);
}

TEST(PriorityQueueTest, MaxHeapProperty) {
	PriorityQueue pq;
	pq.push(10);
	pq.push(30);
	pq.push(20);
	pq.push(5);
	pq.push(25);

	EXPECT_EQ(pq.front(), 30);
	EXPECT_EQ(pq.size(), 5);
}

TEST(PriorityQueueTest, PopLogic) {
	PriorityQueue pq = {10, 30, 20, 5, 25};

	EXPECT_EQ(pq.front(), 30);
	pq.pop();
	EXPECT_EQ(pq.front(), 25);
	pq.pop();
	EXPECT_EQ(pq.front(), 20);
	pq.pop();
	EXPECT_EQ(pq.front(), 10);
	pq.pop();
	EXPECT_EQ(pq.front(), 5);
	pq.pop();

	EXPECT_TRUE(pq.empty());
	EXPECT_EQ(pq.size(), 0);
}

TEST(PriorityQueueTest, InitializerList) {
	PriorityQueue pq = {1, 5, 2, 4, 3};
	EXPECT_EQ(pq.size(), 5);
	EXPECT_EQ(pq.front(), 5);
}

TEST(PriorityQueueTest, ExceptionHandling) {
	PriorityQueue pq;

	EXPECT_THROW(pq.front(), std::out_of_range);
	EXPECT_THROW(pq.pop(), std::out_of_range);

	pq.push(1);
	pq.pop();
	EXPECT_THROW(pq.front(), std::out_of_range);
}

TEST(PriorityQueueTest, DuplicateElements) {
	PriorityQueue pq = {5, 5, 5, 1, 10};
	EXPECT_EQ(pq.front(), 10);
	pq.pop();
	EXPECT_EQ(pq.front(), 5);
	pq.pop();
	EXPECT_EQ(pq.front(), 5);
}
