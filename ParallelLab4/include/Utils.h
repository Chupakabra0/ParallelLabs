#pragma once

#include <stdlib.h>

static double RandDouble(double min, double max);

static double RandDouble(const double min, const double max) {
	return min + (max - min) / RAND_MAX * rand(); // NOLINT(cert-msc30-c, cert-msc50-cpp)
}