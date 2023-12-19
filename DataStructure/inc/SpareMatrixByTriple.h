#pragma once
#include "DataStructure/inc/Matrix.h"

class SpareMatrixByTriple
{
private:
    struct triple{
        int row, col, value;
    };

public:
    int rows,cols,nums;
    triple* data;
    SpareMatrixByTriple(int non_numbers);
    SpareMatrixByTriple(const Matrix& other);
    ~SpareMatrixByTriple();

    void add(int row, int col, int value);
    void remove(int row, int col);
    SpareMatrixByTriple transition();
    SpareMatrixByTriple operator+(const SpareMatrixByTriple& other);
    SpareMatrixByTriple operator*(const SpareMatrixByTriple& other);
};