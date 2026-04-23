#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    double salary;
} Employee;

// small cmp for age, now from smaller to bigger
int compare_by_age(const void *a, const void *b) {
    const Employee *left = a;
    const Employee *right = b;

    return (left->age > right->age) - (left->age < right->age);
}

// salary also sort up
int compare_by_salary(const void *a, const void *b) {
    const Employee *left = a;
    const Employee *right = b;

    return (left->salary > right->salary) - (left->salary < right->salary);
}

// usual alphabet order: A -> Z
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
    qsort(sorted, N, sizeof(Employee), compare_by_age);
    print_employees(sorted, N);
    printf("\n");

    printf("Sorted by Salary:\n");
    memcpy(sorted, employees, sizeof(employees));
    qsort(sorted, N, sizeof(Employee), compare_by_salary);
    print_employees(sorted, N);
    printf("\n");

    printf("Sorted by Name:\n");
    memcpy(sorted, employees, sizeof(employees));
    qsort(sorted, N, sizeof(Employee), compare_by_name);
    print_employees(sorted, N);
    printf("\n");

    return 0;
}
