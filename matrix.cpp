#include "matrix.h"
#include <fstream>
#include <iostream>
#include <typeinfo>

void matrix_input(char *filename, double *matrix, int n){
    std::ifstream file(filename);

    if(!(file.is_open())){
        throw "Can not open file";
    }

    int count = 0;
    char c = ')';

    while(file){
        file >> matrix[count];
        if(typeid(matrix[count]).name() == typeid(c).name()) throw "Incorrect type";
        count++;
        if(count == n * n) break;
    }

    if(count < n * n){
        throw "Not enough data";
    }
    // else if(count > n * n){
    //     throw "Too much data";
    // }
}

void matrix_output(double *matrix, int l, int n, int r){
    for(int i = 0; i < l && i <= r; i++){
        for(int j = 0; j < n && j <= r; j++){
            std::cout << matrix[i * n + j] << " ";
        }
        std::cout << std::endl;
    }
}