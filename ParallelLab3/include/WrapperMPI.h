#pragma once

#include "mpi.h"

int InitMPI(int* argc, char*** argv);
int FinalizeMPI();
int GetSizeMPI(int* size);
int GetWorldRankMPI(int* rank);
