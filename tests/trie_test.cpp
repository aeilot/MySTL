#include <gtest/gtest.h>

#include "include/legacy/trie.h"

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
