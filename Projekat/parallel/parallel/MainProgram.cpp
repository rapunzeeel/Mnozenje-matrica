#include "MainProgram.h"

char* resultFileName;



int mainParallel(int argc, char* argv[]) {
    char* inFileName;
    char* outFileName;

    cout << "                              Multiply matrix parallel                         " << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;

    if (argc != 4)
    {
        error("Error. Wrong number of arguments passed.");
    }

    inFileName = argv[1];
    outFileName = argv[2];
    resultFileName = argv[3];
    
    MatrixDTO mStruct = readFile(inFileName);
    Matrix matrix1{ mStruct.matrix1 };
    Matrix matrix2{ mStruct.matrix2 };
    Matrix matrix{};
    
    if (matrix1.getCol() != matrix2.getRow()) {
        error("Entered matrix isn't of appropriate dimensions!");
    }

    initialization(matrix1, matrix2, matrix);

    parallelFor(matrix, mStruct);
    taskGroupOneCell(matrix, mStruct);
    taskGroupCol(matrix, matrix1, matrix2);
    taskGroupNumberOfCores(matrix1, matrix2, matrix);
    taskGroupRow(matrix, matrix1, matrix2);
  
    Matrix resultMatrix = readResults(resultFileName);
    if(check(resultMatrix, matrix))
        writeFile(outFileName, matrix.getMatrix());
   
    return 0;
}
bool check(Matrix& resultMatrix, Matrix& matrix)
{
    if (checkResult(matrix, resultMatrix)) {
        cout << "Result OK!" << endl;
        return true;   
    }
    else
        error("Result isn't correct!");
    return false;
}
void parallelFor(Matrix& matrix, MatrixDTO& mStruct)
{
    cout << "                               Parallel for                         " << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    matrix.restart();

    tick_count startTime = tick_count::now();
    matrixMultiplicationParallelFor(mStruct, matrix);
    tick_count endTime = tick_count::now();

    matrix.printMatrix();
    cout << endl << "->  Execution time: " << (endTime - startTime).seconds() << "s." << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    Matrix resultMatrix = readResults(resultFileName);
    check(resultMatrix, matrix);
    cout << "----------------------------------------------------------------------------------------------------" << endl;
}

void taskGroupNumberOfCores(Matrix& matrix1, Matrix& matrix2, Matrix& matrix)
{
    cout << "                  Podela zadataka po broju jezgara racunara                " << endl;
    cout <<"----------------------------------------------------------------------------------------------------"<< endl;
    matrix.restart();
    vector<atomic<int>> counter(matrix.getRow() * matrix.getCol());
    initCountersCol(counter, matrix.getRow(), matrix.getCol());

    tick_count startTime = tick_count::now();
    matrixMultiplicationNumberOfCores(matrix1, matrix2, matrix);
    tick_count endTime = tick_count::now();

    matrix.printMatrix();
    cout << endl << "->  Execution time: " << (endTime - startTime).seconds()  << "s." << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    Matrix resultMatrix = readResults(resultFileName);
    check(resultMatrix, matrix);
    cout << "----------------------------------------------------------------------------------------------------" << endl;

}

void taskGroupCol(Matrix& matrix, Matrix& matrix1, Matrix& matrix2)
{
    cout << "                        Podela zadataka po kolonama                            "<< endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    matrix.restart();
    vector<atomic<int>> counter(matrix.getRow() * matrix.getCol());
    initCountersCol(counter, matrix.getRow(), matrix.getCol());

    tick_count startTime = tick_count::now();
    matrixMultiplicationCol(counter, matrix, 0, matrix1.matrix, matrix2.matrix);
    tick_count endTime = tick_count::now();

    matrix.printMatrix();
    cout << endl << "->  Execution time: " << (endTime - startTime).seconds()  << "s." << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    Matrix resultMatrix = readResults(resultFileName);
    check(resultMatrix, matrix);
    cout << "----------------------------------------------------------------------------------------------------" << endl;

}
void taskGroupRow(Matrix& matrix, Matrix& matrix1, Matrix& matrix2)
{
    cout << "                        Podela zadataka po redovima                            " << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    matrix.restart();
    vector<atomic<int>> counter(matrix.getRow() * matrix.getCol());
    initCountersRow(counter, matrix.getRow());

    tick_count startTime = tick_count::now();
    matrixMultiplicationRow(counter, matrix, 0, matrix1, matrix2);
    tick_count endTime = tick_count::now();

    matrix.printMatrix();
    cout << endl << "->  Execution time: " << (endTime - startTime).seconds() << "s." << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    Matrix resultMatrix = readResults(resultFileName);
    check(resultMatrix, matrix);
    cout << "----------------------------------------------------------------------------------------------------" << endl;

}

void taskGroupOneCell(Matrix& matrix, MatrixDTO& mStruct)
{
    matrix.restart();
    cout << "                       Podela zadataka po celijama matrice                      " << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;

    vector<atomic<int>> counter(matrix.getRow() * matrix.getCol());
    initCounters(counter, matrix.getRow(), matrix.getCol());

    tick_count startTime = tick_count::now();
    matrixMultiplicationOneCells(counter, matrix, 0, 0, mStruct);
    tick_count endTime = tick_count::now();

    matrix.printMatrix();
    cout << endl << "->  Execution time: " << (endTime - startTime).seconds() << "s." << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    Matrix resultMatrix = readResults(resultFileName);
    check(resultMatrix, matrix);
    cout << "----------------------------------------------------------------------------------------------------" << endl;

}
