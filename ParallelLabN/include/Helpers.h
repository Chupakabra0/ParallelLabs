#pragma once
#include "ErrorCode.h"

#include "mpi.h"

ErrorCode OpenFile(const char* filePath, MPI_File* file);
ErrorCode CloseFile(MPI_File* file);

ErrorCode AllocateBuffer(char** data, const MPI_Aint* readSize);
ErrorCode FreeBuffer(char* data);

ErrorCode GetStartPosition(MPI_File* file, MPI_Aint* readSize, const int procRank, const int procAmount,
		MPI_Offset* startPosition);

ErrorCode ReadAtAll(MPI_File* file, const MPI_Offset* start, char* buffer, int bufferSize);
