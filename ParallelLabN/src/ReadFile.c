#include "Helpers.h"

#include "stdio.h"
#include <stdlib.h>

#include "mpi.h"

ErrorCode ReadDataFromFile(const char* filePath, const int rank, const int size, const char* procName) {
	ErrorCode error;

	MPI_File* file = (MPI_File*)malloc(sizeof(MPI_File*));

	if ((error = OpenFile(filePath, file)) == NO_ERROR) {
		MPI_Offset* fileSize = (MPI_Offset*)malloc(sizeof(MPI_Offset));
		MPI_Offset* start 	 = (MPI_Offset*)malloc(sizeof(MPI_Offset));
		MPI_Aint*   readSize = (MPI_Aint*)malloc(sizeof(MPI_Aint));

		if ((error = GetStartPosition(file, readSize, rank, size, start)) == NO_ERROR) {
			char* data;

			if ((error = AllocateBuffer(&data, readSize)) == NO_ERROR) {
				data[*readSize] = '\0';
				if ((error = ReadAtAll(file, start, data, (int)*readSize)) == NO_ERROR) {
					fprintf(stdout, "Processor name: %s\nNumber of running processes: %i\nCurrent rank: %i\nData: %s\n\n",
							procName, size, rank, data);
					fflush(stdout);
					error = FreeBuffer(data);
				}
			}
		}
		error = CloseFile(file);

		free(readSize);
		free(start);
		free(fileSize);
	}

	free(file);

	return error;
}
