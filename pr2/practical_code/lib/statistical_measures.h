#ifndef STATISTICAL_MEASURES_H
#define STATISTICAL_MEASURES_H

double mean(double* experiments, int n);
double stddev(double* experiments, int n);
void confidence_interval(double* experiments, int n, double* ci);

#endif // STATISTICAL_MEASURES_H
