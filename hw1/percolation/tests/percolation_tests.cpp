#include "percolation.h"
#include <gtest/gtest.h>

// Fixture for Percolation tests
class PercolationTest : public ::testing::Test {
protected:
    static const int percolation_size = 5;
    Percolation* pc;

    void SetUp() override {
        pc = create_percolation(percolation_size); 
    }

    // Clean up after each test
    void TearDown() override {
        destroy_percolation(pc);
    }
};

TEST_F(PercolationTest, Initialization) {
    EXPECT_EQ(get_opened_count(pc), 0);
    for (int i = 0; i < percolation_size; ++i) {
        for (int j = 0; j < percolation_size; ++j) {
            EXPECT_FALSE(is_opened(pc, i, j));
        }
    }
    EXPECT_FALSE(percolates(pc));
}

TEST_F(PercolationTest, OpenCoordinate) {
    open_coordinate(pc, 0, 0);
    EXPECT_TRUE(is_opened(pc, 0, 0));
    EXPECT_EQ(get_opened_count(pc), 1);
    EXPECT_FALSE(percolates(pc));

    open_coordinate(pc, 0, 0); // duplicate open should not change count
    EXPECT_EQ(get_opened_count(pc), 1);
}

TEST_F(PercolationTest, VerticalPercolation) {
    for (int i = 0; i < percolation_size; ++i) {
        open_coordinate(pc, i, 2);
    }
    EXPECT_TRUE(percolates(pc));
}

TEST_F(PercolationTest, HorizontalPercolation) {
    open_coordinate(pc, 0, 0);
    open_coordinate(pc, 0, 1);
    open_coordinate(pc, 0, 2);
    open_coordinate(pc, 1, 2);
    open_coordinate(pc, 2, 2);
    open_coordinate(pc, 2, 3);
    open_coordinate(pc, 2, 4);
    open_coordinate(pc, 3, 4);
    open_coordinate(pc, 4, 4);

    EXPECT_TRUE(percolates(pc));
}

// Test case: Percolation with diagonal coordinates (should not percolate)
TEST_F(PercolationTest, NoDiagonalPercolation) {
    for (int i = 0; i < percolation_size; ++i) {
        open_coordinate(pc, i, i);
    }
    EXPECT_FALSE(percolates(pc));
}

// Test case: Complex percolation pattern
TEST_F(PercolationTest, ComplexPercolation) {
    open_coordinate(pc, 0, 1);
    open_coordinate(pc, 1, 1);
    open_coordinate(pc, 1, 2);
    open_coordinate(pc, 2, 2);
    open_coordinate(pc, 3, 2);
    open_coordinate(pc, 3, 3);
    EXPECT_FALSE(percolates(pc));

    open_coordinate(pc, 4, 3);
    EXPECT_TRUE(percolates(pc));
}

// Test case: Open count accuracy
TEST_F(PercolationTest, OpenCount) {
    open_coordinate(pc, 0, 0);
    open_coordinate(pc, 0, 1);
    open_coordinate(pc, 1, 1);
    open_coordinate(pc, 1, 1);
    open_coordinate(pc, 4, 4);
    EXPECT_EQ(get_opened_count(pc), 4);
}

// Main function for running tests
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
