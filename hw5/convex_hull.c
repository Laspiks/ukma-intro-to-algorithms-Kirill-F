#include "convex_hull.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static Point p0;

static long long squared_distance(Point a, Point b) {
    // Беремо квадрат відстані, бо корінь тут не потрібен.
    long long dx = (long long) b.x - a.x;
    long long dy = (long long) b.y - a.y;
    return dx * dx + dy * dy;
}

int compare_points(const Point *left, const Point *right) {
    // Спочатку дивимось на y.
    if (left->y != right->y) {
        return (left->y > right->y) - (left->y < right->y);
    }

    // Якщо y однаковий, беремо менший x.
    return (left->x > right->x) - (left->x < right->x);
}

double getAngle(Point origin, Point point) {
    // Кут точки відносно базової точки p0.
    return atan2((double) (point.y - origin.y), (double) (point.x - origin.x));
}

int ccw(Point a, Point b, Point c) {
    long long abx = (long long) b.x - a.x;
    long long aby = (long long) b.y - a.y;
    long long acx = (long long) c.x - a.x;
    long long acy = (long long) c.y - a.y;
    long long cross = abx * acy - aby * acx;

    // Лівий поворот.
    if (cross > 0) {
        return 1;
    }
    // Правий поворот.
    if (cross < 0) {
        return -1;
    }
    // Точки лежать на одній прямій.
    return 0;
}

int compare_by_polar_angle(const Point *left, const Point *right) {
    double left_angle = getAngle(p0, *left);
    double right_angle = getAngle(p0, *right);

    if (left_angle < right_angle) {
        return -1;
    }
    if (left_angle > right_angle) {
        return 1;
    }

    long long left_dist = squared_distance(p0, *left);
    long long right_dist = squared_distance(p0, *right);
    return (left_dist > right_dist) - (left_dist < right_dist);
}

static void swap_points(Point *left, Point *right) {
    Point tmp = *left;
    *left = *right;
    *right = tmp;
}

static int partition_points(Point *points, int low, int high) {
    Point pivot = points[high];
    int i = low - 1;

    // Все, що "менше" pivot, кидаємо вліво.
    for (int j = low; j < high; j++) {
        if (compare_points(&points[j], &pivot) <= 0) {
            i++;
            swap_points(&points[i], &points[j]);
        }
    }

    swap_points(&points[i + 1], &points[high]);
    return i + 1;
}

static void quicksort_points(Point *points, int low, int high) {
    if (low >= high) {
        return;
    }

    int pivot_index = partition_points(points, low, high);
    quicksort_points(points, low, pivot_index - 1);
    quicksort_points(points, pivot_index + 1, high);
}

static void merge_by_polar(Point *points, Point *buffer, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    // Зливаємо дві вже відсортовані частини.
    while (i <= mid && j <= right) {
        if (compare_by_polar_angle(&points[i], &points[j]) <= 0) {
            buffer[k++] = points[i++];
        } else {
            buffer[k++] = points[j++];
        }
    }

    while (i <= mid) {
        buffer[k++] = points[i++];
    }

    while (j <= right) {
        buffer[k++] = points[j++];
    }

    for (int index = left; index <= right; index++) {
        points[index] = buffer[index];
    }
}

static void mergesort_by_polar(Point *points, Point *buffer, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergesort_by_polar(points, buffer, left, mid);
    mergesort_by_polar(points, buffer, mid + 1, right);
    merge_by_polar(points, buffer, left, mid, right);
}

static int remove_duplicates(Point *points, int n) {
    if (n <= 1) {
        return n;
    }

    // Стискаємо однакові точки в одну.
    int unique_count = 1;
    for (int i = 1; i < n; i++) {
        if (points[i].x != points[unique_count - 1].x || points[i].y != points[unique_count - 1].y) {
            points[unique_count++] = points[i];
        }
    }

    return unique_count;
}

int convexHull(const Point *points, int n, Point *hull) {
    if (points == NULL || hull == NULL || n <= 0) {
        return 0;
    }

    // Робимо копію, щоб не псувати вхідний масив.
    Point *sorted = malloc((size_t) n * sizeof(Point));
    if (sorted == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        sorted[i] = points[i];
    }

    // Спершу беремо найнижчу точку, а якщо треба - ще й найлівішу.
    quicksort_points(sorted, 0, n - 1);
    n = remove_duplicates(sorted, n);

    if (n == 1) {
        hull[0] = sorted[0];
        free(sorted);
        return 1;
    }

    // Це базова точка для сортування за кутом.
    p0 = sorted[0];

    if (n > 2) {
        Point *buffer = malloc((size_t) n * sizeof(Point));
        if (buffer == NULL) {
            free(sorted);
            return 0;
        }

        // крутимо точки навколо p0 за полярним кутом
        mergesort_by_polar(sorted, buffer, 1, n - 1);
        free(buffer);
    }

    int hull_size = 0;
    hull[hull_size++] = sorted[0];

    for (int i = 1; i < n; i++) {
        // Поки маємо не лівий поворот, верхню точку стеку викидаємо.
        while (hull_size >= 2 &&
               ccw(hull[hull_size - 2], hull[hull_size - 1], sorted[i]) <= 0) {
            hull_size--;
        }

        // Коли поворот нормальний, додаємо точку в оболонку.
        hull[hull_size++] = sorted[i];
    }

    free(sorted);
    return hull_size;
}

void print_points(const Point *points, int n) {
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)\n", points[i].x, points[i].y);
    }
}
