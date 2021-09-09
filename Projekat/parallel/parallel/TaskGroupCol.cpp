#include "TaskGroupCol.h"
#include <iostream>
using namespace std;

void initCountersCol(vector<atomic<int>>& c, int col, int row) {
    c[0] = 0;
    for (int i = 1; i < row; i++) {
        c[i] = 1;
    }
    for (int i = 1; i < c.size(); i++) {
        if (c[i] != 1)
            c[i] = 0;
    }
}

void sumCol(int j, vector<vector<int>> matrix1, vector<vector<int>> matrix2, vector<vector<int>>& matrix3) {
    for (int i = 0; i < matrix1.size(); i++) {
        for (int k = 0; k < matrix2.size(); k++)
            matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
    }
}

void matrixMultiplicationCol(vector<atomic<int>>& c, Matrix& matrix3, int i, vector<vector<int>> matrix1, vector<vector<int>> matrix2) {
    int col = matrix3.getCol();
    task_group g;
    sumCol(i, matrix1, matrix2, matrix3.matrix);
    if (i < col - 1 && --c[(i + 1)] == 0)
        g.run([&] {matrixMultiplicationCol(c, matrix3, i + 1, matrix1, matrix2); });
    g.wait();
}
