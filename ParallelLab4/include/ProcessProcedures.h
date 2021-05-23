#pragma once

#include "mpi.h"
#include "Matrix.h"

void ProductProcedure(const Matrix* first, const Matrix* second, int commSize, int commRank);
