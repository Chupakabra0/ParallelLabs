#include "Vector.h"

#include "Utils.h"

#define VECTOR_PRINT_ROW 16ll

// I hate this thing, really
static long long i = 0ll;

Vector* AllocateRandomVector(double max) {
	Vector* vector = (Vector*)malloc(sizeof(Vector));
	if (NULL != vector) {
		#pragma omp parallel for default(none) shared(vector, max) private(i)
		for (i = 0ll; i < DIMENSION; ++i) {
			vector->x[i] = RandDouble(max);
		}
	}
	return vector;
}

void PrintVector(FILE* file, const Vector* vector, const char* vectorName) {
	if (NULL == vector || DIMENSION == 0ull) {
		return;
	}
	fprintf(file, "%s: %f", vectorName, vector->x[0]);
	#pragma omp parallel for default(none) shared(vector, file), private(i)
	for (i = 1ll; i < DIMENSION; ++i) {
		if (i % VECTOR_PRINT_ROW == VECTOR_PRINT_ROW - 1ll) {
			fprintf(file, "\n");
		}
		fprintf(file, " %f", vector->x[i]);
	}
	fprintf(file, "\n");
}

double Scalar(const Vector* first, const Vector* second) {
	double result = 0.0;
#pragma omp parallel for default(none) shared(first, second), private(i), reduction(+: result)
	for (i = 0ll; i < DIMENSION; ++i) {
		result += first->x[i] * second->x[i];
	}
	return result;
}
