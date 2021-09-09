#pragma once
#include "tbb/tick_count.h"
#include "tbb/blocked_range2d.h"
#include "tbb/parallel_for.h"
#include "WorkWithFile.h"


using namespace tbb;

class MultiplyMatrixClass
{
private:
    Matrix* const m;
    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;
public: 
    MultiplyMatrixClass(vector<vector<int>> m1, vector<vector<int>> m2, Matrix* m_) : matrix1(m1), matrix2(m2), m(m_) {}
    void operator()(const blocked_range2d<int, int>& r) const;
};
void matrixMultiplicationParallelFor(MatrixDTO& m, Matrix& matrix);
