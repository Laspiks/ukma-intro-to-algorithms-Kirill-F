#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    double salary;
} Employee;

// swap bytes, so function works for any data type
void exch(void *a, void *b, size_t size) {
    unsigned char *left = a;
    unsigned char *right = b;

    for (size_t i = 0; i < size; i++) {
        unsigned char tmp = left[i];
        left[i] = right[i];
        right[i] = tmp;
    }
}

// generic shell sort with cmp function
void shell_sort(void *arr, int N, size_t size, int (*cmp)(const void *, const void *)) {
    char *base = arr;
    int h = 1;

    while (h < N / 3) {
        h = 3 * h + 1; // classic gaps: 1, 4, 13...
    }

    while (h >= 1) {
        for (int i = h; i < N; i++) {
            for (int j = i; j >= h; j -= h) {
                void *current = base + j * size;
                void *prev = base + (j - h) * size;

                if (cmp(current, prev) < 0) {
                    exch(current, prev, size);
                } else {
                    break; // this h-part is already ok
                }
            }
        }
        h /= 3;
    }
}

int compare_by_age(const void *a, const void *b) {
    const Employee *left = a;
    const Employee *right = b;

    return (left->age > right->age) - (left->age < right->age);
}

int compare_by_salary(const void *a, const void *b) {
    const Employee *left = a;
    const Employee *right = b;

    return (left->salary > right->salary) - (left->salary < right->salary);
}

int compare_by_name(const void *a, const void *b) {
    const Employee *left = a;
    const Employee *right = b;

    return strcmp(left->name, right->name);
}

void print_employees(const Employee employees[], int N) {
    for (int i = 0; i < N; i++) {
        printf("%s, Age: %d, Salary: %.2f\n", employees[i].name, employees[i].age,
               employees[i].salary);
    }
}

int main() {
    Employee employees[] = {
        {"Alice", 25, 50000}, {"Bob", 30, 70000}, {"Charlie", 22, 45000}, {"Dave", 35, 80000}};
    Employee sorted[sizeof(employees) / sizeof(employees[0])];
    int N = sizeof(employees) / sizeof(employees[0]);

    printf("Sorted by Age:\n");
    memcpy(sorted, employees, sizeof(employees));
    shell_sort(sorted, N, sizeof(Employee), compare_by_age);
    print_employees(sorted, N);
    printf("\n");

    printf("Sorted by Salary:\n");
    memcpy(sorted, employees, sizeof(employees));
    shell_sort(sorted, N, sizeof(Employee), compare_by_salary);
    print_employees(sorted, N);
    printf("\n");

    printf("Sorted by Name:\n");
    memcpy(sorted, employees, sizeof(employees));
    shell_sort(sorted, N, sizeof(Employee), compare_by_name);
    print_employees(sorted, N);
    printf("\n");

    return 0;
}
