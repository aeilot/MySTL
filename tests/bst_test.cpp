#include <gtest/gtest.h>

#include "include/legacy/bst.h"

class BSTTest : public ::testing::Test {
protected:
	BST bst;
};

TEST_F(BSTTest, InsertAndSearch) {
	EXPECT_FALSE(bst.search(10));
	bst.insert(10);
	bst.insert(5);
	bst.insert(15);

	EXPECT_TRUE(bst.search(10));
	EXPECT_TRUE(bst.search(5));
	EXPECT_TRUE(bst.search(15));
	EXPECT_FALSE(bst.search(100));
}

TEST_F(BSTTest, MinMaxTest) {
	bst.insert(20);
	bst.insert(10);
	bst.insert(30);
	bst.insert(5);
	bst.insert(25);

	EXPECT_EQ(bst.getMin(), 5);
	EXPECT_EQ(bst.getMax(), 30);
}

TEST_F(BSTTest, RemoveTest) {
	bst.insert(50);
	bst.insert(30);
	bst.insert(70);
	bst.insert(20);
	bst.insert(40);

	bst.remove(20);
	EXPECT_FALSE(bst.search(20));
	EXPECT_TRUE(bst.search(30));

	bst.remove(30);
	EXPECT_FALSE(bst.search(30));
	EXPECT_TRUE(bst.search(40));

	bst.insert(60);
	bst.insert(80);
	bst.remove(70);
	EXPECT_FALSE(bst.search(70));
	EXPECT_TRUE(bst.search(60));
	EXPECT_TRUE(bst.search(80));
}

TEST_F(BSTTest, DuplicateInsert) {
	bst.insert(10);
	bst.insert(10);
	EXPECT_TRUE(bst.search(10));
	bst.remove(10);
	EXPECT_FALSE(bst.search(10));
}

TEST_F(BSTTest, EmptyTree) {
	EXPECT_FALSE(bst.search(1));
}
