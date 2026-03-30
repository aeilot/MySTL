#include <gtest/gtest.h>

#include "include/legacy/huffman.h"

TEST(HuffmanTest, SingleWeightHasZeroWeightedPathLength) {
	int weights[] = {7};
	DS::Huffman huffman(weights, 1);

	EXPECT_EQ(huffman.getWPL(), 0);
	ASSERT_NE(huffman.root, nullptr);
	EXPECT_EQ(huffman.root->weight, 7);
	EXPECT_EQ(huffman.root->left, nullptr);
	EXPECT_EQ(huffman.root->right, nullptr);
}

TEST(HuffmanTest, BuildsTreeWithExpectedTotalWeight) {
	int weights[] = {1, 2, 4, 8};
	DS::Huffman huffman(weights, 4);

	ASSERT_NE(huffman.root, nullptr);
	EXPECT_EQ(huffman.root->weight, 15);
	EXPECT_EQ(huffman.getWPL(), 25);
}

TEST(HuffmanTest, EmptyInputThrowsException) {
	EXPECT_THROW(
		{
			int* weights = nullptr;
			DS::Huffman huffman(weights, 0);
		},
		std::exception
	);
}
