#include "convex_hull.h"

#include <stdio.h>

int main(void) {
    Point points[] = {
        {0, 0},
        {2, 0},
        {1, 1},
        {2, 2},
        {1, 3},
        {0, 2}
    };

    int n = (int) (sizeof(points) / sizeof(points[0]));
    Point hull[6];

    int hull_size = convexHull(points, n, hull);

    printf("Points:\n");
    print_points(points, n);

    printf("Convex Hull:\n");
    print_points(hull, hull_size);

    return 0;
}
