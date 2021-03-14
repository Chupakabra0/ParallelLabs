#include <stdlib.h>
#include <stdio.h>

#include "Bonus.h"
#include "mpi.h"

int main(int argc, char** argv) {
	if (MPI_Init(&argc, &argv) != 0) {
		fprintf(stderr, "Failed to init MPI");
		MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
	}

	int* commRank = (int*)malloc(sizeof(int));
	int* commSize = (int*)malloc(sizeof(int));

	MPI_Comm_rank(MPI_COMM_WORLD, commRank);
	MPI_Comm_size(MPI_COMM_WORLD, commSize);

	fprintf(stdout, "%s = %i\n%s = %i\n", "Comm rank", *commRank, "Comm size", *commSize);
	fflush(stdout);

	if (*commRank == 4) {
		SomeOutput(stdout, someStr, 15);
	}

	free(commRank);
	free(commSize);
	MPI_Finalize();

	return EXIT_SUCCESS;
}