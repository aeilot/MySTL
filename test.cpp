#include <gtest/gtest.h>

#include "include/queue.h"
#include "include/stack.h"
#include "include/deque.h"
#include "include/map.h"
#include "include/dsu.h"

TEST(StackTests, EmptyOnNewStack) {
	DS::Stack<int> stack(2);
	EXPECT_TRUE(stack.empty());
}

TEST(StackTests, PushPopIsLifo) {
	DS::Stack<int> stack(2);
	stack.push(1);
	stack.push(2);
	EXPECT_FALSE(stack.empty());
	EXPECT_EQ(stack.pop(), 2);
	EXPECT_EQ(stack.pop(), 1);
	EXPECT_TRUE(stack.empty());
}

TEST(StackTests, PopOnEmptyThrows) {
	DS::Stack<int> stack(1);
	EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST(StackTests, GrowsBeyondInitialCapacity) {
	DS::Stack<int> stack(1);
	stack.push(10);
	stack.push(20);
	stack.push(30);
	EXPECT_EQ(stack.pop(), 30);
	EXPECT_EQ(stack.pop(), 20);
	EXPECT_EQ(stack.pop(), 10);
}

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

TEST(MapTests, EmptyFindReturnsNullopt) {
	DS::Map<int> map;
	EXPECT_EQ(map.find(1), std::nullopt);
}

TEST(MapTests, WriteThenFindReturnsValue) {
	DS::Map<int> map;
	map.write(42, 99);
	EXPECT_EQ(map.find(42), std::optional<int>(99));
}

TEST(MapTests, WriteUpdatesExistingKey) {
	DS::Map<int> map;
	map.write(7, 1);
	map.write(7, 2);
	EXPECT_EQ(map.find(7), std::optional<int>(2));
}

TEST(MapTests, HandlesCollisionChain) {
	DS::Map<int> map;
	int key1 = 5;
	int key2 = key1 + DS::capacity;
	map.write(key1, 10);
	map.write(key2, 20);
	EXPECT_EQ(map.find(key1), std::optional<int>(10));
	EXPECT_EQ(map.find(key2), std::optional<int>(20));
}

TEST(DSUTests, NewSetsAreDistinct) {
	DS::DSU dsu(4);
	EXPECT_EQ(dsu.find(0), 0);
	EXPECT_EQ(dsu.find(1), 1);
	EXPECT_EQ(dsu.find(2), 2);
	EXPECT_EQ(dsu.find(3), 3);
}

TEST(DSUTests, UniteConnectsTwoElements) {
	DS::DSU dsu(3);
	dsu.unite(0, 1);
	EXPECT_EQ(dsu.find(0), dsu.find(1));
	EXPECT_NE(dsu.find(0), dsu.find(2));
}

TEST(DSUTests, UniteConnectsChains) {
	DS::DSU dsu(4);
	dsu.unite(0, 1);
	dsu.unite(2, 3);
	dsu.unite(1, 2);
	EXPECT_EQ(dsu.find(0), dsu.find(3));
}

TEST(DSUTests, UniteSameElementKeepsSetIntact) {
	DS::DSU dsu(2);
	dsu.unite(1, 1);
	EXPECT_EQ(dsu.find(0), 0);
	EXPECT_EQ(dsu.find(1), 1);
	EXPECT_NE(dsu.find(0), dsu.find(1));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}