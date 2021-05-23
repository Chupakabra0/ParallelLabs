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
			fprintf(stdout, "%s\n%s\n", "Not enough args to launch the program", "Example: ParallelLab4 n\nWhere n - count of rows per process") :
			0;
	}
	else {
		srand((unsigned)time(NULL));

		int* processSize = malloc(sizeof(int));
		GetSizeMPI(processSize);

		if (*processSize > 1) {

			const unsigned k = (unsigned)strtoul(argv[1], NULL, 10);

			Matrix* first = AllocateMatrix(1, k * (*processSize - 1u));
			Matrix* second = AllocateSquareMatrix(k * (*processSize - 1u));
			FillRandMatrix(first, -5.0, 5.0);
			FillRandMatrix(second, -5.0, 5.0);

			double start = MPI_Wtime();
			ProductProcedure(first, second, *processSize, *processRank);
			double end = MPI_Wtime();

			*processRank == 0 ? fprintf(stdout, "Total time is %f\n", end - start) : 0;

			FreeMatrix(second);
			FreeMatrix(first);
		}
		else {
			fprintf(stdout, "Not enough processes to launch the program. Need at least 2.\n");
		}

		free(processSize);
	}

	free(processRank);

	return FinalizeMPI();
}