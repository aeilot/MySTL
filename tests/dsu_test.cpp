#include <gtest/gtest.h>

#include "include/legacy/dsu.h"

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
