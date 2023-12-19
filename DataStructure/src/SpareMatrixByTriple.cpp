#include "DataStructure/inc/SpareMatrixByTriple.h"

SpareMatrixByTriple::SpareMatrixByTriple(int non_numbers){
    nums = non_numbers;
    data = new triple[nums];
}

SpareMatrixByTriple::SpareMatrixByTriple(const Matrix& other){
    rows = other.getRows();
    cols = other.getCols();
    nums = rows * cols;
    data = new triple[nums];
    int k = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (other.data[i][j] != 0){
                data[k].row = i;
                data[k].col = j;
                data[k].value = other.data[i][j];
                k++;
            }
        }
    }
}

void SpareMatrixByTriple::add(int row, int col, int value){
    // TODO: Complete the add function
    for (int i = 1; i < this->nums; i++){
        if (data[i].row == row){
            data[i].value = value;
            return;
        }
        if (data[i].row > row && data[i-1].row < row){
            for (int j = this->nums - 1; j > i; j--){
                data[j] = data[j-1];
            }
            data[i].row = row;
            data[i].col = col;
            data[i].value = value;
            return;
        }
    }
    
}