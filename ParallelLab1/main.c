#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Vector.h"
#include "Utils.h"

#define FIRST_RAND_MAX_INDEX 1
#define SECOND_RAND_MAX_INDEX 2
#define THREADS_COUNT_INDEX 3

#define RADIX 10

int main(const int argc, const char** argv) {

	if (argc <= 3) {
		fprintf(stdout, "No args to launch the program...\nExample: lab1.exe 1.1 0.5 1");
		return EXIT_SUCCESS;
	}

	srand((unsigned)time(NULL)); // NOLINT(cert-msc51-cpp)

	const int threads = (int)strtol(argv[THREADS_COUNT_INDEX], NULL, RADIX);

	omp_set_dynamic(0);
	omp_set_num_threads(threads);

	Vector* vector1   = AllocateRandomVector(strtod(argv[FIRST_RAND_MAX_INDEX], NULL));
	Vector* vector2   = AllocateRandomVector(strtod(argv[SECOND_RAND_MAX_INDEX], NULL));

//	PrintVector(stdout, vector1, GET_VAR_NAME(vector1));
//	PrintVector(stdout, vector2, GET_VAR_NAME(vector2));

	double scalar = 0.0;
	const double time = CountTime(Scalar, vector1, vector2, &scalar);

	fprintf(stdout, "Result: %f\nSizeof vectors: %zu\nSpent time: %f seconds\nCount of threads: %i\n",
			scalar, sizeof(Vector) + sizeof(Vector), time, threads);

	FreeVector(vector1);
	FreeVector(vector2);

	return EXIT_SUCCESS;
}
