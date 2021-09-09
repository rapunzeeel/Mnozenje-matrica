#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<string>
#include<vector>
#include<stdexcept>
#include <stdio.h>
#include "Matrix.h"

using namespace std;

void error(const string& s);

class Matrix {
private:
    int col;
    int row;

public:
    vector<vector<int>> matrix;
    Matrix(vector<vector<int>> matrix_) :matrix(matrix_) {
        checkCorrectness();
        col = matrix[0].size();
        row = matrix.size();
    }
    Matrix() {}
    void checkCorrectness();
    void printMatrix();
    int getCol() { return col; }
    int getRow() { return row; }
    void setCol(int c) { col = c; }
    void setRow(int r) { row = r; }
    vector<vector<int>> getMatrix() { return matrix; }
};

void initialization(Matrix matrix1, Matrix matrix2, Matrix& matrix3);
void matrixMultiplication(Matrix& matrix1, Matrix& matrix2, Matrix& matrix3);
bool checkResult(Matrix& correctMatrix, Matrix& resultMatrix);

struct MatrixDTO
{
    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;
};