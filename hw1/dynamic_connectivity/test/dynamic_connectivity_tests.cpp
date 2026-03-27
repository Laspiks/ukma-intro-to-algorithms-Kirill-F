#include "dynamic_connectivity.h"

#include <gtest/gtest.h>

// Fixture for DynamicConnectivity tests
class DynamicConnectivityTest : public ::testing::Test {
protected:
    DynamicConnectivity dc;

    // Set up the initial state for test cases
    void SetUp() override {
        init_dynamic_connectivity(&dc, 10);
    }

    // Clean up state after test cases
    void TearDown() override {
        for (int i = 0; i < CAPACITY; ++i) {
            dc.id[i] = 0;
            dc.sz[i] = 0;
        }
    }
};

TEST_F(DynamicConnectivityTest, Initialization) {
    // Checks if the data structure is correctly initialized with 10 elements,
    // where each element is its own root and has size 1.

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(dc.id[i], i);
        EXPECT_EQ(dc.sz[i], 1);
    }
}

TEST_F(DynamicConnectivityTest, InitializationCapacity) {
    // Checks if the structure initializes correctly with a given capacity.
    // Each element should be its own root, and each component size should be 1.

    init_dynamic_connectivity(&dc, CAPACITY);
    for (int i = 0; i < CAPACITY; ++i) {
        EXPECT_EQ(dc.id[i], i);
        EXPECT_EQ(dc.sz[i], 1);
    }
}

TEST_F(DynamicConnectivityTest, RootFunction) {
    // Tests if the root function correctly finds the root of a given element.
    // Should verify path compression if implemented.

    EXPECT_EQ(root(&dc, 0), 0);
    EXPECT_EQ(root(&dc, 1), 1);
    EXPECT_EQ(root(&dc, 2), 2);
}

TEST_F(DynamicConnectivityTest, ConnectedFunction) {
    // Tests if the connected function correctly determines whether two elements
    // belong to the same component.

    EXPECT_FALSE(connected(&dc, 0, 1));
    EXPECT_TRUE(connected(&dc, 0, 0));
}

TEST_F(DynamicConnectivityTest, UnionFunction) {
    // Tests if the union function correctly merges two components
    // and updates root and size values properly.

    add_union(&dc, 0, 1);
    EXPECT_TRUE(connected(&dc, 0, 1));
    EXPECT_TRUE(connected(&dc, 1, 0));

    add_union(&dc, 1, 2);
    EXPECT_TRUE(connected(&dc, 0, 2));
}

TEST_F(DynamicConnectivityTest, TestTwoConnectedComponents) {
    // Test lecture example, see "Quick-find [greedy approach]: demo"
    add_union(&dc, 4, 3);
    add_union(&dc, 3, 8);
    add_union(&dc, 6, 5);
    add_union(&dc, 9, 4);
    add_union(&dc, 2, 1);
    add_union(&dc, 8, 9);
    add_union(&dc, 5, 0);
    add_union(&dc, 7, 2);
    add_union(&dc, 6, 1);

    EXPECT_TRUE(connected(&dc, 0, 7)); // Component 1: 0, 1, 2, 5, 6, 7
    EXPECT_TRUE(connected(&dc, 3, 9)); // Component 2: 3, 4, 8, 9
    EXPECT_FALSE(connected(&dc, 0, 3)); // Elements from different components should not be connected
}

TEST_F(DynamicConnectivityTest, TestWeightedUnion) {
    // Test case to verify weighted quick-union behavior

    add_union(&dc, 4, 3); // Union operation
    add_union(&dc, 3, 8);
    add_union(&dc, 6, 5);
    add_union(&dc, 9, 4);

    int root_4 = root(&dc, 4);
    int root_9 = root(&dc, 9);

    // Verify that smaller tree is attached to the larger one
    ASSERT_EQ(root_4, root_9); // Both 4 and 9 should have the same root now
    ASSERT_EQ(root(&dc, 3), root_4); // 3 should also point to the same root
    ASSERT_EQ(root(&dc, 8), root_4); // 8 should also point to the same root
}

TEST_F(DynamicConnectivityTest, TestPathCompression) {
    // Test case to verify path compression

    add_union(&dc, 4, 3);
    add_union(&dc, 3, 8);
    add_union(&dc, 6, 5);
    add_union(&dc, 9, 4);
    add_union(&dc, 2, 1);

    // Force path compression by accessing root multiple times
    int root_3_before = root(&dc, 3);
    int root_8_before = root(&dc, 8);

    // Access the same root again to ensure path compression occurred
    int root_3_after = root(&dc, 3);
    int root_8_after = root(&dc, 8);

    // The root should remain the same, but the internal paths should be compressed
    ASSERT_EQ(root_3_before, root_3_after);
    ASSERT_EQ(root_8_before, root_8_after);

    // Check that direct parent of node 3 now points to the root (path compression)
    ASSERT_EQ(dc.id[3], root_3_after);
    ASSERT_EQ(dc.id[8], root_8_after);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
