#include "../convex_hull.h"

#include <assert.h>
#include <stdio.h>

static void assert_point(Point point, int x, int y) {
    assert(point.x == x);
    assert(point.y == y);
}

static void test_basic_convex_hull(void) {
    Point points[] = {{0, 0}, {1, 1}, {2, 2}, {1, 3}, {0, 2}, {2, 0}};
    Point hull[6];

    int hull_size = convexHull(points, 6, hull);

    assert(hull_size == 5);
    assert_point(hull[0], 0, 0);
    assert_point(hull[1], 2, 0);
    assert_point(hull[2], 2, 2);
    assert_point(hull[3], 1, 3);
    assert_point(hull[4], 0, 2);
}

static void test_not_enough_points(void) {
    Point points[] = {{0, 0}, {1, 1}};
    Point hull[2];

    int hull_size = convexHull(points, 2, hull);

    assert(hull_size == 2);
    assert_point(hull[0], 0, 0);
    assert_point(hull[1], 1, 1);
}

static void test_single_point(void) {
    Point points[] = {{1, 1}};
    Point hull[1];

    int hull_size = convexHull(points, 1, hull);

    assert(hull_size == 1);
    assert_point(hull[0], 1, 1);
}

static void test_collinear_points(void) {
    Point points[] = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};
    Point hull[4];

    int hull_size = convexHull(points, 4, hull);

    assert(hull_size == 2);
    assert_point(hull[0], 0, 0);
    assert_point(hull[1], 3, 3);
}

static void test_collinear_points_with_extra_point(void) {
    Point points[] = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {0, 3}};
    Point hull[5];

    int hull_size = convexHull(points, 5, hull);

    assert(hull_size == 3);
    assert_point(hull[0], 0, 0);
    assert_point(hull[1], 3, 3);
    assert_point(hull[2], 0, 3);
}

static void test_random_points(void) {
    Point points[] = {{0, 0}, {2, 0}, {3, 1}, {3, 3}, {2, 3}, {1, 2}};
    Point hull[6];

    int hull_size = convexHull(points, 6, hull);

    // У цьому наборі всі точки лишаються на межі оболонки.
    assert(hull_size == 6);
    assert_point(hull[0], 0, 0);
    assert_point(hull[1], 2, 0);
    assert_point(hull[2], 3, 1);
    assert_point(hull[3], 3, 3);
    assert_point(hull[4], 2, 3);
    assert_point(hull[5], 1, 2);
}

int main(void) {
    test_basic_convex_hull();
    test_not_enough_points();
    test_single_point();
    test_collinear_points();
    test_collinear_points_with_extra_point();
    test_random_points();

    printf("All convex hull tests passed.\n");
    return 0;
}
