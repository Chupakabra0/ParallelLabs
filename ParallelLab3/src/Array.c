#include "Array.h"

#include <stdlib.h>
#include <time.h>

#include "Utils.h"

double* AllocateRandomArray(unsigned long long size, double max) {
	srand((unsigned)time(NULL));
	double* array = (double*)malloc(sizeof(double) * size);
	if (NULL != array) {
		for (unsigned i = 0u; i < size; ++i) {
			array[i] = RandDouble(max);
		}
	}

	return array;
}

void PrintArray(FILE* file, double* begin, const double* end) {
	if (NULL == begin || NULL == end || end == begin) {
		return;
	}
	fprintf(file, "%lf", *(begin++));
	for (double* i = begin; i < end; ++i) {
		fprintf(file, " %lf", *i);
	}
	fprintf(file, "\n");
}
