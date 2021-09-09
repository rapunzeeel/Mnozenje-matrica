#pragma once
#include "tbb/tick_count.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "WorkWithFile.h"
#include <map>

using namespace tbb;
const int N = 4;

void sumCores(Matrix matrix1, Matrix matrix2, int start, int finish, map<int, vector<int>>& mapOfCordinates, Matrix& matrix);
void matrixMultiplicationNumberOfCores(Matrix matrix1, Matrix matrix2, Matrix& matrix);
    