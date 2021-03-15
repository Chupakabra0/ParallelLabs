#pragma once

#include <stdlib.h>

static double Sum(double a, double b);
static double RandDouble(const double max);
double FindSum(double* begin, const double* end, double func(double, double));

static double Sum(double a, double b) {
	return a + b;
}

static double RandDouble(const double max) {
	return max / RAND_MAX * rand() * (rand() % 2 ? -1.0 : 1.0); // NOLINT(cert-msc30-c, cert-msc50-cpp)
}