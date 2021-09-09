#pragma once
#include "ParallelFor.h"
#include "TaskGroupOneCell.h"
#include "TaskGroupCol.h"
#include "TaskGroupNumberOfCores.h"
#include "TaskGroupRow.h"

int mainParallel(int argc, char* argv[]);

bool check(Matrix& resultMatrix, Matrix& matrix);

void parallelFor(Matrix& matrix, MatrixDTO& mStruct);

void taskGroupNumberOfCores(Matrix& matrix1, Matrix& matrix2, Matrix& matrix);

void taskGroupCol(Matrix& matrix, Matrix& matrix1, Matrix& matrix2);

void taskGroupOneCell(Matrix& matrix, MatrixDTO& mStruct);

void taskGroupRow(Matrix& matrix, Matrix& matrix1, Matrix& matrix2);
