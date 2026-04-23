#include "statistical_measures.h"

#include <math.h>

double mean(double* experiments, int n) {
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        sum += experiments[i];
    }

    return sum / n;
}

double stddev(double* experiments, int n) {
    if (n < 2) {
        return 0.0;
    }

    double avg = mean(experiments, n);
    double squared_diff_sum = 0.0;

    for (int i = 0; i < n; i++) {
        double diff = experiments[i] - avg;
        // рахуємо суму квадратів відхилень від середнього
        squared_diff_sum += diff * diff;
    }

    // тут саме вибіркове стандартне відхилення, тому n - 1
    return sqrt(squared_diff_sum / (n - 1));
}

void confidence_interval(double* experiments, int n, double* ci) {
    double avg = mean(experiments, n);
    double sd = stddev(experiments, n);
    double margin = 1.96 * sd / sqrt((double)n);

    // ліва та права межі 95% довірчого інтервалу
    ci[0] = avg - margin;
    ci[1] = avg + margin;
}
