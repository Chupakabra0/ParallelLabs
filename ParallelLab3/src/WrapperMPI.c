#include "WrapperMPI.h"

int InitMPI(const int* argc, char*** argv) {
	return MPI_Init(argc, argv);
}

int FinalizeMPI() {
	return MPI_Finalize();
}

int GetSizeMPI(int* size) {
	return MPI_Comm_size(MPI_COMM_WORLD, size);
}

int GetWorldRankMPI(int* rank) {
	return MPI_Comm_rank(MPI_COMM_WORLD, rank);
}