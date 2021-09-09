#pragma once

#include "Matrix.h"

class readMatrix {
private:
    string delimiter = ";";
    size_t pos1 = 0;
    size_t pos2 = 0;
    int token;
public:
    void makeMatrix(string line, int number, MatrixDTO& m);
};
void generatorMatrix(char* fileNameInput);
MatrixDTO readFile(char* fileNameInput);
Matrix readResults(char* fileNameInput);
void writeFile(char* fileNameOutput, vector<vector<int>> matrix);

