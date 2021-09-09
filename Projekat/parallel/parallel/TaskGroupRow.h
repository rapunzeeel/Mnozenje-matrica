#pragma once
#include "tbb/tick_count.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "WorkWithFile.h"


using namespace tbb;

void initCountersRow(vector<atomic<int>>& c, int col);
vector<int> sumRow(int i, Matrix matrix1, Matrix matrix2, Matrix& matrix3);
void matrixMultiplicationRow(vector<atomic<int>>& c, Matrix& matrix3, int i, Matrix matrix1, Matrix matrix2);