#include <gtest/gtest.h>

#include "include/legacy/splay.h"

namespace {

class SplayTreeTest : public ::testing::Test {
protected:
	DS::SplayTree tree;

	void SeedTree() {
		for (int value : {10, 5, 15, 3, 7, 12, 18}) {
			tree.insert(value);
		}
	}
};

}  // namespace

TEST_F(SplayTreeTest, EmptyTreeOperations) {
	EXPECT_FALSE(tree.search(42));
	EXPECT_THROW(tree.getMin(), std::out_of_range);
	EXPECT_THROW(tree.getMax(), std::out_of_range);
	EXPECT_THROW(tree.getKth(1), std::out_of_range);
}

TEST_F(SplayTreeTest, InsertSearchAndExtrema) {
	SeedTree();

	EXPECT_TRUE(tree.search(10));
	EXPECT_TRUE(tree.search(3));
	EXPECT_TRUE(tree.search(18));
	EXPECT_FALSE(tree.search(100));
	EXPECT_EQ(tree.getMin(), 3);
	EXPECT_EQ(tree.getMax(), 18);
}

TEST_F(SplayTreeTest, KthAndRankFollowSortedOrder) {
	SeedTree();

	EXPECT_EQ(tree.getKth(1), 3);
	EXPECT_EQ(tree.getKth(4), 10);
	EXPECT_EQ(tree.getKth(7), 18);
	EXPECT_THROW(tree.getKth(0), std::out_of_range);
	EXPECT_THROW(tree.getKth(8), std::out_of_range);

	EXPECT_EQ(tree.getRank(3), 1);
	EXPECT_EQ(tree.getRank(10), 4);
	EXPECT_EQ(tree.getRank(18), 7);
	EXPECT_EQ(tree.getRank(13), 6);
}

TEST_F(SplayTreeTest, DuplicateInsertDoesNotCreateExtraNode) {
	tree.insert(10);
	tree.insert(10);

	EXPECT_TRUE(tree.search(10));
	EXPECT_EQ(tree.getKth(1), 10);
	EXPECT_THROW(tree.getKth(2), std::out_of_range);

	tree.remove(10);
	EXPECT_FALSE(tree.search(10));
}

TEST_F(SplayTreeTest, RemoveMaintainsSearchAndOrder) {
	SeedTree();

	tree.remove(3);
	EXPECT_FALSE(tree.search(3));
	EXPECT_EQ(tree.getKth(1), 5);

	tree.remove(15);
	EXPECT_FALSE(tree.search(15));
	EXPECT_EQ(tree.getRank(18), 5);

	tree.remove(10);
	EXPECT_FALSE(tree.search(10));
	EXPECT_EQ(tree.getMin(), 5);
	EXPECT_EQ(tree.getMax(), 18);
	EXPECT_EQ(tree.getKth(1), 5);
	EXPECT_EQ(tree.getKth(2), 7);
	EXPECT_EQ(tree.getKth(3), 12);
	EXPECT_EQ(tree.getKth(4), 18);
	EXPECT_THROW(tree.getKth(5), std::out_of_range);
}
