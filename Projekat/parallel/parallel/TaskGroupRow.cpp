#include "TaskGroupRow.h"

void initCountersRow(vector<atomic<int>>& c, int col) {
    c[0] = 0;
    for (int i = 1; i < col; i++) {
        c[i] = 1;
    }
    for (int i = 1; i < c.size(); i++) {
        if (c[i] != 1)
            c[i] = 0;
    }
}
vector<int> sumRow(int i, Matrix matrix1, Matrix matrix2, Matrix& matrix3) {
    for (int j = 0; j < matrix2.getCol(); j++) {
        for (int k = 0; k < matrix2.getRow(); k++)
            matrix3.matrix[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
    }
    return matrix3.matrix[i];
}
void matrixMultiplicationRow(vector<atomic<int>>& c, Matrix& matrix3, int i, Matrix matrix1, Matrix matrix2) {
    int row = matrix3.getRow();
    task_group g;
    matrix3.matrix[i] = sumRow(i, matrix1, matrix2, matrix3);
    if (i < row - 1 && --c[(i + 1)] == 0)
        g.run([&] {matrixMultiplicationRow(c, matrix3, i + 1, matrix1, matrix2); });
    g.wait();
}