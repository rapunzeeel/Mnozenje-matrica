#pragma once
#include "tbb/tick_count.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "WorkWithFile.h"


using namespace tbb;

void initCountersCol(vector<atomic<int>>& c, int col, int row);
void sumCol(int j, vector<vector<int>> matrix1, vector<vector<int>> matrix2, vector<vector<int>>& matrix3);
void matrixMultiplicationCol(vector<atomic<int>>& c, Matrix& matrix3, int i, vector<vector<int>> matrix1, vector<vector<int>> matrix2);
