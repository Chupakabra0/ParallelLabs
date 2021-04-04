#include "ProcessProcedures.h"

Matrix* ProductProcedure(const Matrix* first, const Matrix* second, const int commSize, const int commRank) {
	if (first == NULL || second == NULL) {
		return NULL;
	}

	const unsigned segmentSize = first->rowsCount / (commSize - 1);

	if (commRank == 0u) {
		fprintf(stdout, "////////////////////////////////\n");
		fprintf(stdout, "Hello from %d process\n", commRank);
		PrintMatrix(stdout, first);
		fprintf(stdout, "--------------------------------\n");
		PrintMatrix(stdout, second);
		fprintf(stdout, "////////////////////////////////\n");
		fflush(stdout);

		unsigned destination = 1u;

		// TODO: REMOVE REPEAT CODE
		for (unsigned i = 0u; i < first->rowsCount; ++i) {
			MPI_Send(first->matrix[i], (int)first->columnsCount, MPI_DOUBLE, (int)destination, 0, MPI_COMM_WORLD);

			if (i % segmentSize == segmentSize - 1u) {
				++destination;
			}
		}

		Matrix* temp = TransposeMatrix(second);
		// TODO: REMOVE REPEAT CODE
		for (int i = 1; i < commSize; ++i) {
			for (unsigned j = 0u; j < temp->rowsCount; ++j) {
				MPI_Send(temp->matrix[j], (int)temp->columnsCount, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
			}
		}

		free(temp);
		return NULL;
	}
	else {
		Matrix* left = AllocateMatrix(segmentSize, first->columnsCount);

		for (unsigned i = 0u; i < left->rowsCount; ++i) {
			MPI_Recv(left->matrix[i], (int)left->columnsCount, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
					MPI_STATUSES_IGNORE);
		}

		Matrix* temp = AllocateMatrix(second->rowsCount, second->columnsCount);

		for (unsigned i = 0u; i < temp->rowsCount; ++i) {
			MPI_Recv(temp->matrix[i], (int)temp->columnsCount, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
					MPI_STATUSES_IGNORE);
		}

		Matrix* right = TransposeMatrix(temp);
		FreeMatrix(temp);

		fprintf(stdout, "////////////////////////////////\n");
		fprintf(stdout, "Hello from %d process\n", commRank);
		PrintMatrix(stdout, left);
		fprintf(stdout, "--------------------------------\n");
		PrintMatrix(stdout, right);
		fprintf(stdout, "////////////////////////////////\n");
		fflush(stdout);

		return left;
	}
}
