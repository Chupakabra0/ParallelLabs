#pragma once

#include <stdlib.h>
#include <stdio.h>

#define ARRAY_RAND_MAX 100.0

static void FreeArray(double* array);
double* AllocateRandomArray(unsigned long long size, double max);
void PrintArray(FILE* file, double* begin, const double* end);

static void FreeArray(double* array) {
	free(array);
}
