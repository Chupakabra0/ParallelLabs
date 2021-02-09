#pragma once

#include <stdio.h>
#include <malloc.h>

#define DIMENSION 268435455ll

typedef struct Vector {
	double x[DIMENSION];
} Vector;

Vector* AllocateRandomVector(double max);
static void FreeVector(Vector* vector);
void PrintVector(FILE* file, const Vector* vector, const char* vectorName);
double Scalar(const Vector* first, const Vector* second);

static void FreeVector(Vector* vector) {
	free(vector);
}
