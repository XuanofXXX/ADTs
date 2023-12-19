#include "../inc/Matrix.h"

Matrix::Matrix(const int rows, const int cols)
{  
    this->rows = rows; this->cols = cols;
    data = new int *[rows];
    for (int i = 0; i < rows; i++)
        data[i] = new int[cols];
}

Matrix::Matrix(const Matrix& other){
    rows = other.getRows();
    cols = other.getCols();
    data = new int *[rows];
    for (int i = 0; i < rows; i++){
        data[i] = new int[cols];
        for (int j = 0; j < cols; j++){
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < this->rows; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}

Matrix Matrix::operator+(const int other){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            data[i][j] += other;
        }
    }
}

Matrix Matrix::operator+(const Matrix& other){
    if (rows != other.getRows() || cols != other.getCols()){
        throw "Matrix size not match";
    }
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            res.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return res;
}

Matrix Matrix::operator*(const Matrix& other){
    if (cols != other.getRows()){
        throw "Matrix size not match";
    }
    // TODO: Complete the matrix multiplication
    for (int i = 0; i < this->rows; i++)
    {
        /* code */
    }
}