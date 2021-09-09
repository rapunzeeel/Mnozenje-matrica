#include "Matrix.h"

void initialization(Matrix matrix1, Matrix matrix2, Matrix& matrix3) {
    matrix3.setCol(matrix2.getCol());
    matrix3.setRow(matrix1.getRow());
    vector<int> row;
    for (int i = 0; i < matrix2.getCol(); i++) {
        row.push_back(0);
    }
    for (int i = 0; i < matrix1.getRow(); i++) {
        matrix3.matrix.push_back(row);
    }
}

void Matrix::printMatrix() {
    for (int row = 0; row < matrix.size(); row++) {
        for (int col = 0; col < matrix[0].size(); col++) {
            cout << "\t" << matrix[row][col];
        }
        cout << endl;
    }
}

void Matrix::checkCorrectness() {
    int correctSizeCol = matrix[0].size();
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i].size() != correctSizeCol) {
            error("The matrix doesn't have a good fromat!");
        }
    }

}

void matrixMultiplication(Matrix& matrix1, Matrix& matrix2, Matrix& matrix3) {
    for (int row = 0; row < matrix1.getRow(); row++) {
        for (int col = 0; col < matrix2.getCol(); col++) {
            for (int k = 0; k < matrix2.getRow(); k++) {
                matrix3.matrix[row][col] += matrix1.getMatrix()[row][k] * matrix2.getMatrix()[k][col];
            }
        }
    }
}

bool checkResult(Matrix& correctMatrix, Matrix& resultMatrix) {
    for (int i = 0; i < correctMatrix.getRow(); i++) {
        for (int j = 0; j < correctMatrix.getCol(); j++) {
            if (correctMatrix.matrix[i][j] != resultMatrix.matrix[i][j])
                return false;
        }
    }
    return true;
}

void error(const string& s) {
    cerr << "ERROR. " << s << endl;
    exit(0);
}