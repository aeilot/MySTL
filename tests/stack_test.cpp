#include <gtest/gtest.h>

#include "include/smart/stack.h"

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
