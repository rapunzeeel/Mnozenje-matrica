#include "ParallelFor.h"


void MultiplyMatrixClass::operator()(const blocked_range2d<int, int>& r) const {
    Matrix* s = m;
    for (int row = r.rows().begin(); row != r.rows().end(); ++row) {
        for (int col = r.cols().begin(); col < r.cols().end(); col++) {
            float sum = 0;
            for (int k = 0; k < matrix2.size(); ++k) 
                sum += matrix1[row][k] * matrix2[k][col];
            s->matrix[row][col] = sum;
        }
    }

}
void matrixMultiplicationParallelFor(MatrixDTO& m, Matrix& matrix) {
    MultiplyMatrixClass mclass(m.matrix1,m.matrix2, &matrix);
    parallel_for(blocked_range2d<int, int>(0, m.matrix1.size(), 0, m.matrix2[0].size()), mclass);
}