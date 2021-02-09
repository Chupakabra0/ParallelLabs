#include "Utils.h"

#include <time.h>

double CountTime(double function(const Vector*, const Vector*), const Vector* first, const Vector* second,
		double* result) {
	const clock_t begin = clock();
	*result             = function(first, second);
	const clock_t end   = clock();
	return (double)(end - begin) / CLOCKS_PER_SEC;
}

