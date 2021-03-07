#pragma once
#include <stdio.h>

extern const char* someStr;

void SleepMs(int milliseconds);
void SomeOutput(FILE* file, const char* str, int delayMilliseconds);