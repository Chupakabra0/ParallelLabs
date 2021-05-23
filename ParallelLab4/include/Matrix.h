#pragma once

#include <stdio.h>
#include <malloc.h>

typedef struct Matrix {
	double** matrix;
	unsigned rowsCount;
	unsigned columnsCount;
} Matrix;

static Matrix* AllocateSquareMatrix(unsigned rowsAndColumnsCount);
static Matrix* AllocateMatrix(unsigned rowsCount, unsigned columnsCount);
static void FreeMatrix(Matrix* matrix);
void PrintMatrix(FILE* file, const Matrix* matrix);
void FillZeroMatrix(Matrix* matrix);
void FillRandMatrix(Matrix* matrix, double min, double max);
Matrix* ProductMatrix(const Matrix* first, const Matrix* second);
Matrix* TransposeMatrix(const Matrix* matrix);

static Matrix* AllocateSquareMatrix(const unsigned rowsAndColumnsCount) {
	return AllocateMatrix(rowsAndColumnsCount, rowsAndColumnsCount);
}

static Matrix* AllocateMatrix(const unsigned rowsCount, const unsigned columnsCount) {
	Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
	matrix->rowsCount = rowsCount;
	matrix->columnsCount = columnsCount;
	matrix->matrix = (double**)malloc(sizeof(double*) * matrix->rowsCount);

	for (unsigned i = 0u; i < matrix->rowsCount; ++i) {
		matrix->matrix[i] = (double*)malloc(sizeof(double) * matrix->columnsCount);
	}

	return matrix;
}

static void FreeMatrix(Matrix* matrix) {
	for (unsigned i = 0u; i < matrix->rowsCount; ++i) {
		free(matrix->matrix[i]);
	}

	free(matrix->matrix);
	free(matrix);
}
