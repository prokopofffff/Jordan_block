#include <iostream>
#include "funcs.h"

int main(){
    double *A = new double[9];
    double *B = new double[9];
    double *C = new double[9];

    std::cout << "Starting..." << std::endl;

    A[0] = 1;
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

    multiply(A, B, C, 3, 3, 3, 3);

    for(int i = 0; i < 9; i++){
        std::cout << C[i] << " "; 
    }
}