#include "WorkWithFile.h"


void readMatrix::makeMatrix(string line, int number, MatrixDTO& m) {
    if (line.find(";") != -1) {
        vector<int> p;
        while ((pos2 = line.find(delimiter)) != string::npos) {
            token = stoi(line.substr(pos1, pos2));
            p.push_back(token);
            line.erase(pos1, pos2 + delimiter.length());
        }
        if (number == 1)
            m.matrix1.push_back(p);
        else
            m.matrix2.push_back(p);
    }
 
}
MatrixDTO readFile(char* fileNameInput) {
    string line;
    bool found = false;
    MatrixDTO matrixDTO;
    readMatrix m = readMatrix();

    ifstream inputFile(fileNameInput);
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            if (line.find("-") != -1) {
                found = true;
                continue;
            }
            if (found) {
                m.makeMatrix(line, 2, matrixDTO);
            }
            else {
                m.makeMatrix(line, 1, matrixDTO);
            }
        }
        inputFile.close();
    }
    return matrixDTO;
}
Matrix readResults(char* fileNameInput) {
    string line;
    string delimiter = ";";
    size_t pos1 = 0;
    size_t pos2 = 0;
    int token;
    Matrix resultsMatrix;

    ifstream inputFile(fileNameInput);
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            if (line.find(";") != -1) {
                vector<int> p;
                while ((pos2 = line.find(delimiter)) != string::npos) {
                    token = stoi(line.substr(pos1, pos2));
                    p.push_back(token);
                    line.erase(pos1, pos2 + delimiter.length());
                }
                resultsMatrix.matrix.push_back(p);
            }
        }
        inputFile.close();
    }
    return resultsMatrix;
}
void writeFile(char* fileNameOutput, vector<vector<int>> matrix) {
    ofstream outputFile;
    outputFile.open(fileNameOutput);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            outputFile << "\t" << matrix[i][j];
        }
        outputFile << endl;
    }
    outputFile.close();
}