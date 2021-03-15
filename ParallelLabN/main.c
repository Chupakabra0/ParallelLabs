#include <stdlib.h>
#include <stdio.h>

#include "ReadFile.h"
#include "ProcessInfo.h"

#include "mpi.h"

int main(int argc, char** argv) {
	if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
		fprintf(stderr, "Failed to init MPI");
		MPI_Abort(MPI_COMM_WORLD, INIT_MPI_ERROR);
	}

	ErrorCode error = NO_ERROR;

	if (argc < 2) {
		int* rank = malloc(sizeof(int));

		if ((error = GetCommutatorRank(MPI_COMM_WORLD, rank)) == NO_ERROR && *rank == 0) {
			fprintf(stdout, "%s\n%s\n", "Not enough args...", "Example: ParallelLabN.exe file.txt");
		}

		free(rank);
	}
	else {
		char procName[MPI_MAX_PROCESSOR_NAME];

		if ((error = GetProcessorName(procName)) == NO_ERROR) {
			int* rank = malloc(sizeof(int));

			if ((error = GetCommutatorRank(MPI_COMM_WORLD, rank)) == NO_ERROR) {
				int* size = malloc(sizeof(int));

				if ((error = GetCommutatorSize(MPI_COMM_WORLD, size)) == NO_ERROR) {
					if ((error = ReadDataFromFile(argv[1], *rank, *size, procName)) != NO_ERROR) {
						fprintf(stderr, "Error #%i: %s\n", error, "read file error!");
					}
				}

				free(size);
			}
			else {
				fprintf(stderr, "Error #%i: %s\n", error, "get commutator size error!");
			}

			free(rank);
		}
		else {
			fprintf(stderr, "Error #%i: %s\n", error, "get commutator rank error!");
		}
	}

	MPI_Finalize();

	return error;
}