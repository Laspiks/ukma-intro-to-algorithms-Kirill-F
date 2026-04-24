#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

typedef struct {
    int x;
    int y;
} Point;

int compare_points(const Point *left, const Point *right);
double getAngle(Point origin, Point point);
int ccw(Point a, Point b, Point c);
int compare_by_polar_angle(const Point *left, const Point *right);
int convexHull(const Point *points, int n, Point *hull);
void print_points(const Point *points, int n);

#endif
