#include "RankProcedures.h"

#include <stdlib.h>
#include <stdio.h>

#include "Array.h"
#include "Utils.h"
#include "mpi.h"

#define SEND_TO_ZERO_PROCESS  0
#define SEND_TO_FIRST_PROCESS 1

#define GET_FROM_ZERO_PROCESS  0
#define GET_FROM_FIRST_PROCESS 1

#define FIRST_TASK  1
#define SECOND_TASK 2

 void ZeroRankProcedure(int size) {
	double* array = AllocateRandomArray(size, ARRAY_RAND_MAX);
	MPI_Send(array, size, MPI_DOUBLE, SEND_TO_FIRST_PROCESS, FIRST_TASK, MPI_COMM_WORLD);

	double* sum = (double*)malloc(sizeof(double));
	MPI_Recv(sum, 1, MPI_DOUBLE, GET_FROM_FIRST_PROCESS, SECOND_TASK, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	fprintf(stdout, "0 process got value: sum = %lf", *sum);
	fprintf(stdout, "\n");
	fflush(stdout);

	free(sum);
	FreeArray(array);
}

void FirstRankProcedure(int size) {
	double* array = (double*)malloc(sizeof(double) * size);
	MPI_Recv(array, size, MPI_DOUBLE, GET_FROM_ZERO_PROCESS, FIRST_TASK, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	fprintf(stdout, "1 process got value: array = ");
	PrintArray(stdout, array, array + size);
	fprintf(stdout, "\n");
	fflush(stdout);

	double* sum = (double*)malloc(sizeof(double));
	*sum = FindSum(array, array + size, Sum);

	MPI_Send(sum, 1, MPI_DOUBLE, SEND_TO_ZERO_PROCESS, SECOND_TASK, MPI_COMM_WORLD);

	free(sum);
	free(array);
}

void RankProcedure(int rank, int arraySize) {
	rank == 0 ? ZeroRankProcedure(arraySize) : (rank == 1 ? FirstRankProcedure(arraySize) : 0);
}
