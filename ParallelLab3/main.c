#include <stdlib.h>
#include <stdio.h>

#include "mpi.h"

typedef enum ErrorCode {
	NO_ERROR,
	FILE_OPEN_ERROR,
	FILE_CLOSE_ERROR,
	FILE_READ_ERROR,
	MEMORY_ALLOC_ERROR,
	MEMORY_FREE_ERROR,
	GET_FILE_SIZE_ERROR,
	GET_PROC_NAME_ERROR,
	GET_RANK_ERROR,
	GET_SIZE_ERROR
} ErrorCode;

ErrorCode Func(const char* filename, int rank, int size, char* procName, int procNameSize) {
	///////////////////////////////
	MPI_File* file = (MPI_File*)malloc(sizeof(MPI_File));

	if (MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_RDONLY, MPI_INFO_NULL, file) != MPI_SUCCESS) {
		free(file);
		return FILE_OPEN_ERROR;
	}
	///////////////////////////////

	///////////////////////////////
	MPI_Offset* fileSize 	= (MPI_Offset*)malloc(sizeof(MPI_Offset));

	if (MPI_File_get_size(*file, fileSize) != MPI_SUCCESS) {
		MPI_File_close(file);
		free(fileSize);
		free(file);
		return GET_FILE_SIZE_ERROR;
	}
	--*fileSize;
	///////////////////////////////

	///////////////////////////////
	MPI_Offset globalStart, globalEnd, dataSize;

	dataSize    = *fileSize / size;
	globalStart = dataSize * rank;

	if (rank == size - 1) {
		globalEnd = *fileSize - 1;
	}
	else {
		globalEnd = globalStart + dataSize;
	}

	dataSize = globalEnd - globalStart + 2;

	///////////////////////////////
	char* data;

	if (MPI_Alloc_mem(dataSize + 1, MPI_INFO_NULL, &data) != MPI_SUCCESS) {
		MPI_File_close(file);
		free(fileSize);
		free(file);
		return MEMORY_ALLOC_ERROR;
	}
	data[dataSize] = '\0';

	if (MPI_File_read_all(*file, data, (int)dataSize, MPI_CHAR, MPI_STATUSES_IGNORE) != MPI_SUCCESS) {
		MPI_Free_mem(data);
		MPI_File_close(file);
		free(fileSize);
		free(file);
		return FILE_READ_ERROR;
	}

	///////////////////////////////

	fprintf(stdout, "Processor name: %s\nNumber of running processes: %i\nCurrent rank: %i\nData: %s\n\n",
			procName, size, rank, data);

	///////////////////////////////

	if (MPI_Free_mem(data) != MPI_SUCCESS) {
		MPI_File_close(file);
		free(fileSize);
		free(file);
		return MEMORY_FREE_ERROR;
	}

	if (MPI_File_close(file) != MPI_SUCCESS) {
		free(fileSize);
		free(file);
		return FILE_CLOSE_ERROR;
	}

	free(fileSize);
	free(file);
	///////////////////////////////

	return NO_ERROR;
}

int main(int argc, char** argv) {
	if (MPI_Init(&argc, &argv) != 0) {
		fprintf(stderr, "Failed to init MPI");
		MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
	}
	setvbuf(stdout, NULL, _IONBF , (size_t)0);

	if (argc < 2) {
		fprintf(stdout, "%s\n%s", "Not enough args...", "Example: lab3.exe file.txt");
		return EXIT_SUCCESS;
	}

	///////////////////////////////

	char procName[MPI_MAX_PROCESSOR_NAME];
	int* procNameSize = malloc(sizeof(int));
	if (MPI_Get_processor_name(procName, procNameSize) != MPI_SUCCESS) {
		free(procNameSize);
		return GET_PROC_NAME_ERROR;
	}

	///////////////////////////////

	///////////////////////////////

	int* rank = malloc(sizeof(int));
	if (MPI_Comm_rank(MPI_COMM_WORLD, rank) != MPI_SUCCESS) {
		free(procNameSize);
		free(rank);
		return GET_RANK_ERROR;
	}

	///////////////////////////////

	///////////////////////////////

	int* size = malloc(sizeof(int));
	if (MPI_Comm_size(MPI_COMM_WORLD, size) != MPI_SUCCESS) {
		free(procNameSize);
		free(rank);
		free(size);
		return GET_SIZE_ERROR;
	}

	///////////////////////////////

	ErrorCode errorCode = Func(argv[1], *rank, *size, procName, *procNameSize);

	MPI_Finalize();
	free(procNameSize);
	free(rank);
	free(size);

	return errorCode;
}