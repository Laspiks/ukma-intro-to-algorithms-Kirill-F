#include <stdio.h>
#include "lib/statistical_measures.h"

int main() {
    double data[] = {10.0, 12.0, 23.0, 22.0, 23.0, 16.0, 23.0, 21.0, 16.0};
    int n = sizeof(data) / sizeof(data[0]);

    double avg = mean(data, n);
    double sd = stddev(data, n);
    double ci[2];
    confidence_interval(data, n, ci);

    printf("Mean: %.2f\n", avg);
    printf("Standard Deviation: %.2f\n", sd);
    printf("95%% Confidence Interval: [%.2f, %.2f]\n", ci[0], ci[1]);

    return 0;
}
