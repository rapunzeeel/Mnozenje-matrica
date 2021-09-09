#include "TaskGroupNumberOfCores.h"


void sumCores(Matrix matrix1, Matrix matrix2, int start, int finish, map<int,vector<int>>& mapOfCordinates, Matrix& matrix) {
    map<int, vector<int>>::iterator it;
    for (it = mapOfCordinates.begin(); it != mapOfCordinates.end(); it++)
    {
        if (((*it).first >= start) && ((*it).first < finish)) {
            int i = (*it).second[0];
            int j = (*it).second[1];
            for (int k = 0; k < matrix2.getRow(); ++k) {
                matrix.matrix[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
            }
        }
    }
}

void matrixMultiplicationNumberOfCores(Matrix matrix1, Matrix matrix2, Matrix& matrix) {
    task_group g;
    int a = matrix.getRow() * matrix.getCol() / N;
    map<int, vector<int>> mapOfCordinates;
    int counter = 0;
    for (int i = 0; i < matrix.getRow(); i++) {
        for (int j = 0; j < matrix.getCol(); j++) {
            vector<int> cordinates;
            cordinates.push_back(i);
            cordinates.push_back(j);
            mapOfCordinates.insert(std::pair<int, vector<int>>(counter, cordinates));
            counter++;
        }
    }
    g.run([&] {sumCores(matrix1, matrix2, 0, a, mapOfCordinates, matrix); });
    g.run([&] {sumCores(matrix1, matrix2, a, 2 * a, mapOfCordinates, matrix); });
    g.run([&] {sumCores(matrix1, matrix2, 2*a, 3*a, mapOfCordinates, matrix); });
    g.run([&] {sumCores(matrix1, matrix2, 3*a, 4*a, mapOfCordinates, matrix); });
    g.wait();
}