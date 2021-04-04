#include "Matrix.h"

#include "Utils.h"

void PrintMatrix(FILE* file, const Matrix* matrix) {
	for (unsigned i = 0u; i < matrix->rowsCount; ++i) {
		for (unsigned j = 0u; j < matrix->columnsCount; ++j) {
			if (j == 0u) {
				fprintf(file, "%f", matrix->matrix[i][j]);
			}
			else {
				fprintf(file, " %f", matrix->matrix[i][j]);
			}
		}
		fprintf(file, "\n");
	}
}

void FillRandMatrix(Matrix* matrix, const double min , const double max) {
	for (unsigned  i = 0u; i < matrix->rowsCount; ++i) {
		for (unsigned j = 0u; j < matrix->columnsCount; ++j) {
			matrix->matrix[i][j] = RandDouble(min, max);
		}
	}
}

void FillZeroMatrix(Matrix* matrix) {
	for (unsigned  i = 0u; i < matrix->rowsCount; ++i) {
		for (unsigned j = 0u; j < matrix->columnsCount; ++j) {
			matrix->matrix[i][j] = 0.0;
		}
	}
}

Matrix* ProductMatrix(const Matrix* first, const Matrix* second) {
	if (first->columnsCount != second->rowsCount) {
		return NULL;
	}

	Matrix* result = AllocateMatrix(first->rowsCount, second->columnsCount);
	FillZeroMatrix(result);

	for (unsigned i = 0u; i < first->rowsCount; ++i) {
		for (unsigned j = 0u; j < second->columnsCount; ++j) {
			for (unsigned k = 0u; k < second->columnsCount; ++k) {
				result->matrix[i][j] += first->matrix[i][k] * second->matrix[k][j];
			}
		}
	}

	return result;
}
