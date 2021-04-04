#include "ProcessProcedures.h"

Matrix* ProductProcedure(const Matrix* first, const Matrix* second, const int commSize, const int commRank) {
	if (first == NULL || second == NULL) {
		return NULL;
	}

	const unsigned segmentSize = first->rowsCount / (commSize - 1);

	if (commRank == 0u) {
		fprintf(stdout, "Hello from %d process\n", commRank);
		PrintMatrix(stdout, first);
		fprintf(stdout, "--------------------------------\n");

		unsigned destination = 1u;

		for (unsigned i = 0u; i < first->rowsCount; ++i) {
			MPI_Send(first->matrix[i], (int)first->columnsCount, MPI_DOUBLE, (int)destination, (int)destination,
					MPI_COMM_WORLD);

			if (i % (segmentSize + 1) == segmentSize) {
				++destination;
			}
		}

		return NULL;
	}
	else {
		Matrix* result = AllocateMatrix(segmentSize, first->columnsCount);

		for (unsigned i = 0u; i < result->rowsCount; ++i) {
			MPI_Recv(result->matrix[i], (int)result->columnsCount, MPI_DOUBLE, 0, (int)commRank, MPI_COMM_WORLD,
					MPI_STATUSES_IGNORE);
		}
		fprintf(stdout, "Hello from %d process\n", commRank);
		PrintMatrix(stdout, result);
		fprintf(stdout, "--------------------------------\n");
		return result;
	}
}
