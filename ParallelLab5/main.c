#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include "mpi.h"

static double RandDouble(const double max) {
    return max / RAND_MAX * rand() * (rand() % 2 ? -1.0 : 1.0); // NOLINT(cert-msc30-c, cert-msc50-cpp)
}

double* AllocateRandomArray(unsigned long long size, double max) {
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
}

static void FreeArray(double* array) {
    free(array);
}

int main(int argc, char* argv[]) {
	srand(time(NULL));

	int size, rank;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	double* array       = AllocateRandomArray(size, 3.0);
	double* resultArray = AllocateRandomArray(size, 3.0);
	double  resultSum       = 0.0;
    double  resultProd      = 1.0;
    double  resultMin       = -DBL_MAX;

	MPI_Bcast(array, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	MPI_Reduce(&array[rank], &resultSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&array[rank], &resultProd, 1, MPI_DOUBLE, MPI_PROD, 0, MPI_COMM_WORLD);
    MPI_Reduce(&array[rank], &resultMin, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);

	MPI_Gather(&array[rank], 1, MPI_DOUBLE, resultArray, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if (rank == 0) {
        fprintf(stdout, "Sum = %f\n", resultSum);
        fprintf(stdout, "Prod = %f\n", resultProd);
        fprintf(stdout, "Min = %f\n", resultMin);
        fprintf(stdout, "Array: ");

		PrintArray(stdout, resultArray, resultArray + size);
	}

    FreeArray(array);
    FreeArray(resultArray);

	MPI_Finalize();

    return EXIT_SUCCESS;
}
