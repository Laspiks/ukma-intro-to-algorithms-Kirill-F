#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

static Point p0;

// Спочатку шукаємо найнижчу точку, а якщо y однаковий - лівішу.
static int compare_by_y_then_x(const void *a, const void *b) {
    const Point *left = a;
    const Point *right = b;

    if (left->y != right->y) {
        return (left->y > right->y) - (left->y < right->y);
    }

    return (left->x > right->x) - (left->x < right->x);
}

static long long squared_distance(Point a, Point b) {
    long long dx = (long long)b.x - a.x;
    long long dy = (long long)b.y - a.y;
    return dx * dx + dy * dy;
}

// Знак векторного добутку показує, куди повертаємо:
// > 0 - проти годинникової, < 0 - за годинниковою.
static long long cross_product(Point a, Point b, Point c) {
    long long abx = (long long)b.x - a.x;
    long long aby = (long long)b.y - a.y;
    long long acx = (long long)c.x - a.x;
    long long acy = (long long)c.y - a.y;
    return abx * acy - aby * acx;
}

// Сортуємо відносно p0 за полярним кутом.
// Якщо точки лежать на одному промені, ближча має йти першою.
static int compare_by_polar_angle(const void *a, const void *b) {
    const Point *left = a;
    const Point *right = b;

    long long turn = cross_product(p0, *left, *right);
    if (turn > 0) {
        return -1;
    }
    if (turn < 0) {
        return 1;
    }

    // Якщо кут однаковий, залишаємо ближчу точку раніше.
    long long dist_left = squared_distance(p0, *left);
    long long dist_right = squared_distance(p0, *right);
    return (dist_left > dist_right) - (dist_left < dist_right);
}

static void print_points(const Point points[], int n) {
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)\n", points[i].x, points[i].y);
    }
}

int main(void) {
    int n = 0;

    printf("Enter number of points: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Wrong input for number of points.\n");
        return 1;
    }

    if (n == 0) {
        return 0;
    }

    Point *points = malloc((size_t)n * sizeof(Point));
    if (points == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter point %d (x y): ", i);
        if (scanf("%d %d", &points[i].x, &points[i].y) != 2) {
            fprintf(stderr, "Wrong input for point %d.\n", i);
            free(points);
            return 1;
        }
    }

    // Ставимо p0 на початок масиву.
    qsort(points, (size_t)n, sizeof(Point), compare_by_y_then_x);
    p0 = points[0];

    // Решту точок впорядковуємо навколо p0.
    if (n > 1) {
        qsort(points + 1, (size_t)(n - 1), sizeof(Point), compare_by_polar_angle);
    }

    printf("p0 = (%d, %d)\n", points[0].x, points[0].y);
    printf("Sorted points:\n");
    print_points(points, n);

    free(points);
    return 0;
}
