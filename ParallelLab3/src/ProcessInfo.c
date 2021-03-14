#include "ProcessInfo.h"

#include <stdlib.h>

ErrorCode GetCommutatorRank(const MPI_Comm commutator, int* rank) {
	if (MPI_Comm_rank(commutator, rank) != MPI_SUCCESS) {
		return GET_RANK_ERROR;
	}

	return NO_ERROR;
}

ErrorCode GetCommutatorSize(const MPI_Comm commutator, int* size) {
	if (MPI_Comm_size(commutator, size) != MPI_SUCCESS) {
		return GET_SIZE_ERROR;
	}

	return NO_ERROR;
}

ErrorCode GetProcessorName(char* name) {
	int* nameSize = malloc(sizeof(int));

	if (MPI_Get_processor_name(name, nameSize) != MPI_SUCCESS) {
		return GET_SIZE_ERROR;
	}

	free(nameSize);

	return NO_ERROR;
}
