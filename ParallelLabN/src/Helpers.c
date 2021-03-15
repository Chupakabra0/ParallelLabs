#include "Helpers.h"

#include <stdlib.h>

#include "mpi.h"

ErrorCode OpenFile(const char* filePath, MPI_File* file) {
	if (MPI_File_open(MPI_COMM_WORLD, filePath, MPI_MODE_RDONLY, MPI_INFO_NULL, file) != MPI_SUCCESS) {
		return FILE_OPEN_ERROR;
	}

	return NO_ERROR;
}

ErrorCode CloseFile(MPI_File* file) {
	if (MPI_File_close(file) != MPI_SUCCESS) {
		return FILE_CLOSE_ERROR;
	}

	return NO_ERROR;
}

ErrorCode GetFileSize(MPI_File* file, MPI_Offset* fileSize) {
	if (MPI_File_get_size(*file, fileSize) != MPI_SUCCESS) {
		return GET_FILE_SIZE_ERROR;
	}
	--*fileSize;

	return NO_ERROR;
}

ErrorCode GetReadSize(MPI_File* file, const int procAmount, MPI_Aint* readSize) {
	MPI_Offset* totalFileSize = (MPI_Offset*)malloc(sizeof(MPI_Offset));
	ErrorCode error;

	if ((error = GetFileSize(file, totalFileSize)) == NO_ERROR) {
		*readSize = *totalFileSize / procAmount;
	}

	free(totalFileSize);

	return error;
}

ErrorCode GetStartPosition(MPI_File* file, MPI_Aint* readSize, const int procRank, const int procAmount,
		MPI_Offset* startPosition) {
	ErrorCode error;

	if ((error = GetReadSize(file, procAmount, readSize)) == NO_ERROR) {
		*startPosition = *readSize * procRank;
	}

	return error;
}

ErrorCode AllocateBuffer(char** data, const MPI_Aint* readSize) {
	if (MPI_Alloc_mem(*readSize + 1, MPI_INFO_NULL, data) != MPI_SUCCESS) {
		return MEMORY_ALLOC_ERROR;
	}

	return NO_ERROR;
}

ErrorCode FreeBuffer(char* data) {
	if (MPI_Free_mem(data) != MPI_SUCCESS) {
		return MEMORY_FREE_ERROR;
	}

	return NO_ERROR;
}

ErrorCode ReadAtAll(MPI_File* file, const MPI_Offset* start, char* buffer, int bufferSize) {
	if (MPI_File_read_at_all(*file, *start, buffer, bufferSize, MPI_CHAR, MPI_STATUSES_IGNORE) != MPI_SUCCESS) {
		return FILE_READ_ERROR;
	}

	return NO_ERROR;
}
