#pragma once

#include "ErrorCode.h"

#include "mpi.h"

ErrorCode GetCommutatorRank(MPI_Comm commutator, int* rank);
ErrorCode GetCommutatorSize(MPI_Comm commutator, int* size);

ErrorCode GetProcessorName(char* name);
