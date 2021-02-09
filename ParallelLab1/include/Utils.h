#pragma once

#include <stdlib.h>

#include "Vector.h"

static double RandDouble(double max);

double CountTime(double function(const Vector*, const Vector*), const Vector* first, const Vector* second,
		double* result);

static double RandDouble(const double max) {
	return max / RAND_MAX * rand(); // NOLINT(cert-msc30-c, cert-msc50-cpp)
}
