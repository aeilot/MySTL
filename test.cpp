#include <gtest/gtest.h>

#include "include/queue.h"
#include "include/stack.h"
#include "include/deque.h"
#include "include/map.h"
#include "include/dsu.h"
#include "include/trie.h"

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

TEST(TrieTests, EmptyTrieFindReturnsZero) {
	DS::Trie trie;
	EXPECT_EQ(trie.find("apple"), 0);
}

TEST(TrieTests, InsertThenFindReturnsCount) {
	DS::Trie trie;
	trie.insert("apple");
	EXPECT_EQ(trie.find("apple"), 1);
}

TEST(TrieTests, InsertSameWordMultipleTimesCountsOccurrences) {
	DS::Trie trie;
	trie.insert("apple");
	trie.insert("apple");
	EXPECT_EQ(trie.find("apple"), 2);
}

TEST(TrieTests, FindPrefixWithoutExactWordReturnsZero) {
	DS::Trie trie;
	trie.insert("apple");
	EXPECT_EQ(trie.find("app"), 0);
}

TEST(TrieTests, DistinguishesDifferentWords) {
	DS::Trie trie;
	trie.insert("apple");
	trie.insert("app");
	EXPECT_EQ(trie.find("apple"), 1);
	EXPECT_EQ(trie.find("app"), 1);
	EXPECT_EQ(trie.find("apples"), 0);
}


#include "include/list/vector.h"

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

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}