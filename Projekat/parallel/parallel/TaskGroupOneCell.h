#pragma once
#include "tbb/tick_count.h"
#include "tbb/blocked_range2d.h"
#include "tbb/parallel_for.h"
#include "WorkWithFile.h"


using namespace tbb;

void initCounters(vector<atomic<int>>& c, int row, int col);

int sum(int i, int j, MatrixDTO& m, Matrix& matrix3);
void matrixMultiplicationOneCells(vector<atomic<int>>& c, Matrix& matrix3, int i, int j, MatrixDTO& m);

