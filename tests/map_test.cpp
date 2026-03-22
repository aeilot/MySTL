#include <gtest/gtest.h>

#include "include/legacy/map.h"

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
