#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ProcessProcedures.h>

#include "Matrix.h"
#include "WrapperMPI.h"

int main(int argc, char** argv) {
	if (InitMPI(&argc, &argv)) {
		fprintf(stderr, "Error: %s!\n", "failed to init MPI");
		MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
	}

	int* processRank = malloc(sizeof(int));
	GetWorldRankMPI(processRank);

	if (argc < 2) {
		*processRank == 0 ?
			fprintf(stdout, "%s\n%s\n", "Not enough args to launch the program", "Example: ParallelLab4") :
			0;
	}
	else {
		srand((unsigned)time(NULL));

		int* processSize = malloc(sizeof(int));
		GetSizeMPI(processSize);

		// TODO: helper function with input checks
		const unsigned k = (unsigned)strtoul(argv[1], NULL, 10);

		Matrix* first = AllocateSquareMatrix(k * (*processSize - 1u));
		Matrix* second = AllocateSquareMatrix(k * (*processSize - 1u));
		FillRandMatrix(first, -5.0, 5.0);
		FillRandMatrix(second, -5.0, 5.0);

		ProductProcedure(first, second, *processSize, *processRank);

//		PrintMatrix(stdout, first);
//		fprintf(stdout, "------------------------------\n");
//
//		PrintMatrix(stdout, second);
//		fprintf(stdout, "------------------------------\n");

		FreeMatrix(second);
		FreeMatrix(first);

		free(processSize);
	}

	free(processRank);

	return FinalizeMPI();
}