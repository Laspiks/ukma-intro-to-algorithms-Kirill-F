#include <gtest/gtest.h>

#define N 10

int sz[N];  // sz array to track the sz of each tree

bool connected__quick_find(const int* id, int p, int q) {
    return id[p] == id[q];
}

void union__quick_find(int* id, int p, int q) {
    int pid = id[p];
    int qid = id[q];

    for (int i = 0; i < N; ++i) {
        if (id[i] == pid) {
            id[i] = qid;
        }
    }
}

int root__quick_union(const int* id, int i) {
    while (i != id[i]) {
        i = id[i];
    }
    return i;
}

bool connected__quick_union(const int* id, int p, int q) {
    return root__quick_union(id, p) == root__quick_union(id, q);
}

void union__quick_union(int* id, int p, int q) {
    int root_p = root__quick_union(id, p);
    int root_q = root__quick_union(id, q);
    id[root_p] = root_q;
}

int root__quick_union_path_compression(int* id, int i) {
    while (i != id[i]) {
        id[i] = id[id[i]];  // трошки стискаємо шлях
        i = id[i];
    }
    return i;
}

void union__weighted_quick_union(int* id, int p, int q) {
    int root_p = root__quick_union_path_compression(id, p);
    int root_q = root__quick_union_path_compression(id, q);

    if (root_p == root_q) {
        return;
    }

    // менше дерево вішаємо на більше
    if (sz[root_p] < sz[root_q]) {
        id[root_p] = root_q;
        sz[root_q] += sz[root_p];
    } else {
        id[root_q] = root_p;
        sz[root_p] += sz[root_q];
    }
}

class QuickUnionTest : public ::testing::Test {
protected:
    int id[N];

    void SetUp() override {
        for (int i = 0; i < N; ++i) {
            id[i] = i;
            sz[i] = 1;
        }
    }

    void TearDown() override {
        // Clean up code, if necessary (e.g., resetting variables, releasing resources)
    }
};

TEST_F(QuickUnionTest, Connected__QuickFind) {
    id[3] = id[4] = 1;
    EXPECT_TRUE(connected__quick_find(id, 3, 4));
    EXPECT_FALSE(connected__quick_find(id, 3, 5));
}

TEST_F(QuickUnionTest, Union__QuickFind) {
    id[1] = id[3] = 7;
    union__quick_find(id, 1, 5);

    EXPECT_EQ(id[1], id[5]);
    EXPECT_EQ(id[3], id[5]);
    EXPECT_NE(id[0], id[5]);
}

TEST_F(QuickUnionTest, Root__QuickUnion) {
    id[3] = 4;
    id[4] = 6;
    id[6] = 6;

    EXPECT_EQ(root__quick_union(id, 3), 6);
    EXPECT_EQ(root__quick_union(id, 4), 6);
}

TEST_F(QuickUnionTest, Connected__QuickUnion) {
    id[1] = 2;
    id[2] = 5;
    id[7] = 5;

    EXPECT_TRUE(connected__quick_union(id, 1, 7));
    EXPECT_FALSE(connected__quick_union(id, 1, 8));
}

TEST_F(QuickUnionTest, Union__QuickUnion) {
    id[1] = 2;
    id[2] = 2;
    id[4] = 6;
    id[6] = 6;

    union__quick_union(id, 1, 4);

    EXPECT_EQ(root__quick_union(id, 1), root__quick_union(id, 4));
    EXPECT_EQ(id[2], 6);
}

TEST_F(QuickUnionTest, Union__WeightedQuickUnion) {
    id[1] = 1;
    id[2] = 1;
    sz[1] = 2;

    id[4] = 4;
    id[5] = 4;
    id[6] = 4;
    sz[4] = 3;

    union__weighted_quick_union(id, 1, 4);

    EXPECT_EQ(root__quick_union(id, 1), 4);
    EXPECT_EQ(root__quick_union(id, 2), 4);
    EXPECT_EQ(sz[4], 5);
}

TEST_F(QuickUnionTest, Root__QuickUnionPathCompression) {
    id[1] = 2;
    id[2] = 3;
    id[3] = 4;
    id[4] = 4;

    EXPECT_EQ(root__quick_union_path_compression(id, 1), 4);
    EXPECT_EQ(id[1], 3);
    EXPECT_EQ(id[2], 3);
}
