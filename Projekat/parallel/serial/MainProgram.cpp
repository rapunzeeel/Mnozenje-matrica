#include "MainProgram.h"


int mainSerial(int argc, char* argv[]){
    cout << "                           Multiply matrix serial                                " << endl;
    cout << "-------------------------------------------------------------------------------" << endl;

    if (argc != 4)
    {
        error("Error. Wrong number of arguments passed.");
    }

    char* inFileName = argv[1];
    char* outFileName = argv[2];
    char* resultFileName = argv[3];

    //generatorMatrix(inFileName);

    MatrixDTO mStruct = readFile(inFileName);
    Matrix matrix1{ mStruct.matrix1 };
    Matrix matrix2{ mStruct.matrix2 };
    Matrix matrix{};

    if (matrix1.getCol() != matrix2.getRow()) {
        error("Entered matrix isn't of appropriate dimensions!");
    }
    initialization(matrix1, matrix2, matrix);

    tick_count startTime = tick_count::now();
    matrixMultiplication(matrix1, matrix2, matrix);
    tick_count endTime = tick_count::now();
    matrix.printMatrix();
    cout << endl << "->  Execution time: " << (endTime - startTime).seconds() << "s." << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    
   
    cout << "->  Result: " << endl << endl;
    Matrix resultMatrix = readResults(resultFileName);
    resultMatrix.printMatrix();

    cout << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    if (checkResult(matrix, resultMatrix)) {
        cout << "Result OK!" << endl;
        writeFile(outFileName, matrix.getMatrix());
    }else
        error("Result isn't correct!");
   

    return 0;
}
