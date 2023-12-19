#pragma once

class Matrix
{
private:

public:
    int rows, cols;
    int **data;
    Matrix(const int rows, const int cols);
    Matrix(const Matrix& other);
    
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    Matrix operator+(const Matrix& other);
    Matrix operator+(const int other);
    Matrix operator-(const Matrix& other);
    Matrix operator-(const int other);
    Matrix operator*(const Matrix& other);
    Matrix operator*(const int other);
    ~Matrix();
};


