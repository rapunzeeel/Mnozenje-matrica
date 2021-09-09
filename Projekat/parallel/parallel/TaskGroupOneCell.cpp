#include "TaskGroupOneCell.h"


void initCounters(vector<atomic<int>>& c, int row, int col) {
    c[0] = 0;
    for (int i = 1; i < col; i++) {
        c[i] = 1;
    }
    for (int i = col; i <= row * col - col; i += col) {
        c[i] = 1;
    }
    for (int i = 1; i < c.size(); i++) {
        if (c[i] != 1)
            c[i] = 2;
    }
}
int sum(int i, int j, MatrixDTO& m, Matrix& matrix3) {
    for (int k = 0; k < m.matrix2.size(); k++)
        matrix3.matrix[i][j] += m.matrix1[i][k] * m.matrix2[k][j];
    return matrix3.matrix[i][j];
}
void matrixMultiplicationOneCells(vector<atomic<int>>& c, Matrix& matrix3, int i, int j, MatrixDTO& m) {
    task_group g;
    int row = matrix3.getRow();
    int col = matrix3.getCol();
    matrix3.matrix[i][j] = sum(i, j, m, matrix3);
    if (j < col - 1 && --c[i * col + (j + 1)] == 0)
        g.run([&] {matrixMultiplicationOneCells(c, matrix3, i, j + 1, m); });
    if (i < row - 1 && --c[(i + 1) * col + j] == 0)
        g.run([&] {matrixMultiplicationOneCells(c, matrix3, i + 1, j, m); });
    g.wait();
}
