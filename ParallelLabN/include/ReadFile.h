#pragma once
#include "ErrorCode.h"

ErrorCode ReadDataFromFile(const char* filePath, const int rank, const int size, const char* procName);
