#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Matrix.h"
#include "WrapperMPI.h"

int main(int argc, char** argv) {
	if (InitMPI(&argc, &argv)) {
		fprintf(stderr, "Error: %s!\n", "failed to init MPI");
		MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
	}

	srand((unsigned)time(NULL));

	Matrix* first  = AllocateSquareMatrix(3);
	Matrix* second = AllocateSquareMatrix(3);
	FillRandMatrix(first, -5.0, 5.0);
	FillRandMatrix(second, -5.0, 5.0);

	Matrix* third = ProductMatrix(first, second);

	PrintMatrix(stdout, first);
	fprintf(stdout, "------------\n");

	PrintMatrix(stdout, second);
	fprintf(stdout, "------------\n");

	PrintMatrix(stdout, third);
	fprintf(stdout, "------------\n");

	FreeMatrix(third);
	FreeMatrix(second);
	FreeMatrix(first);

//	int* processSize = malloc(sizeof(int));
//	GetSizeMPI(processSize);
//
//	int* processRank = malloc(sizeof(int));
//	GetWorldRankMPI(processRank);
//
//	if (argc < 1) {
//		*processRank == 0 ?
//			fprintf(stdout, "%s\n%s\n", "Not enough args to launch the program", "Example: ParallelLab4") :
//			0;
//	}
//	else {
//
//	}
//
//	free(processSize);
	return FinalizeMPI();
}