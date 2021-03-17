#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "WrapperMPI.h"
#include "RankProcedures.h"

int main(int argc, char** argv) {
	if (InitMPI(&argc, &argv)) {
		fprintf(stderr, "Error: %s!\n", "failed to init MPI");
		MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
	}

	int* size = malloc(sizeof(int));

	GetSizeMPI(size);

	if (*size >= 2) {
		int* rank = malloc(sizeof(int));
		GetWorldRankMPI(rank);

		if (argc < 2) {
			*rank == 0 ?
				fprintf(stdout, "%s\n%s\n", "Not enough args to launch the program", "Example: ParallelLab3 100") : 0;

			return FinalizeMPI();
		}

		char* error;
		int arraySize = strtol(argv[1], &error, 10);
		if ((*error != 0 && !isspace((unsigned char)*error)) || arraySize <= 0) {
			*rank == 0 ? fprintf(stderr, "Error: %s!\n", "bad argument") : 0;

			return FinalizeMPI();
		}

		RankProcedure(*rank, arraySize);

		free(rank);
	}
	else {
		fprintf(stderr, "Error: %s %i!\n", "not enough processes! Need 2, you have", *size);
	}

	free(size);

	return FinalizeMPI();
}
