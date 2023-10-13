#include <iostream>
#include "funcs.h"

int main(){
    double *A = new double[9];
    double *B = new double[9];
    double *C = new double[9];

    std::cout << "Starting..." << std::endl;

    A[0] = 10;
    A[1] = 2;
    A[2] = 3;
    A[3] = 4;
    A[4] = 5;
    A[5] = 6;
    A[6] = 7;
    A[7] = 8;
    A[8] = 9;

    B[0] = 9;
    B[1] = 8;
    B[2] = 7;
    B[3] = 6;
    B[4] = 5;
    B[5] = 4;
    B[6] = 3;
    B[7] = 2;
    B[8] = 1;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            C[i * 3 + j] = i == j ? 1 : 0;
        }
    }

    int flag = inverse(A, C, 3);

    std::cout << flag << std::endl;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << C[i * 3 + j] << " "; 
        }
        std::cout << std::endl;
    }
}