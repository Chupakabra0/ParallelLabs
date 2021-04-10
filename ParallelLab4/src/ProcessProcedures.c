#include "ProcessProcedures.h"
#include "Utils.h"

#define DEBUG

void ProductProcedure(const Matrix* first, const Matrix* second, const int commSize, const int commRank) {
	// if NULL, stop procedure
	if (first == NULL || second == NULL) {
		return;
	}

	// calculate count of arrays to send to the one process, excluding 0-process
	unsigned segmentSize = first->rowsCount / (commSize - 1);
	if (segmentSize == 0u) {
		++segmentSize;
	}

	if (commRank == 0u) {
#if defined(DEBUG)
		fprintf(stdout, "\n");
		fprintf(stdout, "Hello from %d process\n", commRank);
		PrintMatrix(stdout, first);
		fprintf(stdout, "--------------------------------\n");
		PrintMatrix(stdout, second);
		//
#endif

		unsigned destination = 1u;
		// sending of first matrix to unique processes
		if (first->rowsCount >= (int)commSize) {
			for (unsigned i = 0u; i < first->rowsCount; ++i) {
				MPI_Send(first->matrix[i], (int)first->columnsCount, MPI_DOUBLE, (int)destination, 0, MPI_COMM_WORLD);

				if (i % segmentSize == segmentSize-1u) {
					++destination;
				}
			}
		}
		else {
			for (int i = 1; i < commSize; ++i) {
				for (unsigned j = 0u; j < first->rowsCount; ++j) {
					MPI_Send(first->matrix[j], (int)first->columnsCount, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
				}
			}
		}

		// transposing to send one array
		Matrix* temp = TransposeMatrix(second);
		// sending transposed second matrix to all processes except 0-process
		for (int i = 1; i < commSize; ++i) {
			for (unsigned j = 0u; j < temp->rowsCount; ++j) {
				MPI_Send(temp->matrix[j], (int)temp->columnsCount, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
			}
		}

		free(temp);

		// getting result matrix
		Matrix* result = AllocateMatrix(first->rowsCount, second->columnsCount);
		destination = 1u;

		for (unsigned i = 0u; i < result->rowsCount; ++i) {
					MPI_Recv(result->matrix[i], (int)result->columnsCount, MPI_DOUBLE, (int)destination, 0,
							MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

			if (i % segmentSize == segmentSize - 1u) {
				++destination;
			}
		}

#if defined(DEBUG)
		fprintf(stdout, "--------------------------------\n");
		PrintMatrix(stdout, result);
		fprintf(stdout, "\n");
		fflush(stdout);
#endif
	}
	else {
		// receiving of the first matrix
		Matrix* left = AllocateMatrix(segmentSize, first->columnsCount);
		if (first->rowsCount >= (int)commSize) {
			for (unsigned i = 0u; i < left->rowsCount; ++i) {
				MPI_Recv(left->matrix[i], (int)left->columnsCount, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
						MPI_STATUSES_IGNORE);
			}
		}
		else {
			for (unsigned i = 0u; i < left->rowsCount; ++i) {
				MPI_Recv(left->matrix[i], (int)first->columnsCount, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			}
		}

		// receiving of the second matrix
		Matrix* temp = AllocateMatrix(second->columnsCount, second->rowsCount);
		for (unsigned i = 0u; i < temp->rowsCount; ++i) {
			MPI_Recv(temp->matrix[i], (int)temp->columnsCount, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
					MPI_STATUSES_IGNORE);
		}

		// transposing to get original matrix
		Matrix* right = TransposeMatrix(temp);
		FreeMatrix(temp);

#if defined(DEBUG)
		// DEBUG
		fprintf(stdout, "\n");
		fprintf(stdout, "Hello from %d process\n", commRank);
		PrintMatrix(stdout, left);
		fprintf(stdout, "--------------------------------\n");
		PrintMatrix(stdout, right);
		//
#endif
		// product matrix
		double start = MPI_Wtime();
		Matrix* result = ProductMatrix(left, right);
		double end = MPI_Wtime();

		FreeMatrix(left);
		FreeMatrix(right);
#if defined(DEBUG)
		// DEBUG
		fprintf(stdout, "--------------------------------\n");
		PrintMatrix(stdout, result);
		fprintf(stdout, "Time: %f\n", end - start);
		fflush(stdout);
		//
#endif
		// sending result to 0-process
		for (unsigned i = 0u; i < result->rowsCount; ++i) {
			MPI_Send(result->matrix[i], (int)result->columnsCount, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
		}
		FreeMatrix(result);
	}
}
