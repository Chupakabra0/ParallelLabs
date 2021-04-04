#include "Utils.h"

double FindSum(double* begin, const double* end, double func(double, double)) {
	double sum = 0.0;
	for (double* i = begin; i < end; ++i) {
		sum = func(sum, *i);
	}

	return sum;
}
