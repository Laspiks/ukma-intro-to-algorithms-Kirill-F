#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    double half_full_mean;
    double full_mean;
} SimulationResult;

static int parse_positive_int(const char *text, int fallback) {
    if (text == NULL) {
        return fallback;
    }

    char *end = NULL;
    long value = strtol(text, &end, 10);
    if (*text == '\0' || *end != '\0' || value <= 0 || value > INT32_MAX) {
        return fallback;
    }

    return (int)value;
}

static double run_single_experiment(int spaces, int cars) {
    bool *occupied = calloc((size_t)spaces, sizeof(bool));
    if (occupied == NULL) {
        fprintf(stderr, "Cannot allocate memory for %d parking spaces.\n", spaces);
        exit(1);
    }

    long long total_displacement = 0;

    for (int car = 0; car < cars; ++car) {
        int desired = rand() % spaces;
        int pos = desired;
        // In lecture these numbers match better if we count probes:
        // first checked place also counts, even if car parks immediately.
        int displacement = 1;

        // Just like linear probing from lecture:
        // if place is busy, go right until free slot appears.
        while (occupied[pos]) {
            pos = (pos + 1) % spaces;
            displacement++;
        }

        occupied[pos] = true;
        total_displacement += displacement;
    }

    free(occupied);
    return (double)total_displacement / (double)cars;
}

static SimulationResult run_monte_carlo(int spaces, int trials) {
    double half_sum = 0.0;
    double full_sum = 0.0;
    int half_cars = spaces / 2;

    for (int trial = 0; trial < trials; ++trial) {
        half_sum += run_single_experiment(spaces, half_cars);
        full_sum += run_single_experiment(spaces, spaces);
    }

    SimulationResult result;
    result.half_full_mean = half_sum / (double)trials;
    result.full_mean = full_sum / (double)trials;
    return result;
}

int main(int argc, char *argv[]) {
    int spaces = parse_positive_int(argc > 1 ? argv[1] : NULL, 10000);
    int trials = parse_positive_int(argc > 2 ? argv[2] : NULL, 200);
    const double pi = 3.14159265358979323846;

    srand((unsigned)time(NULL));

    SimulationResult result = run_monte_carlo(spaces, trials);

    double half_theory = 1.5;
    double full_theory = sqrt(pi * (double)spaces / 8.0);

    printf("Knuth parking problem Monte Carlo\n");
    printf("M = %d, trials = %d\n\n", spaces, trials);

    printf("Half-full case (%d cars):\n", spaces / 2);
    printf("  simulated mean displacement = %.6f\n", result.half_full_mean);
    printf("  theory from lecture        = %.6f\n", half_theory);
    printf("  abs difference             = %.6f\n\n", fabs(result.half_full_mean - half_theory));

    printf("Full case (%d cars):\n", spaces);
    printf("  simulated mean displacement = %.6f\n", result.full_mean);
    printf("  theory from lecture        = %.6f\n", full_theory);
    printf("  abs difference             = %.6f\n", fabs(result.full_mean - full_theory));

    return 0;
}
