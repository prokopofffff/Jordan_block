#include "jordan.h"
#include "funcs.h"
#include <iostream>
#include <pthread.h>

// struct args_row{
//     double* A;
//     double* B;
//     double* C;
//     double* block;
//     double* dop_mat;
//     int n;
//     int m;
//     int row;
//     int col;
//     int k;
//     int l;
// };

// void* multRow(void* args){
//     args_row* a = (args_row*)args;
// }

int Jordan(double *A, double *B, double *X, double *C, double *block, double *dop_mat, int n, int m){
    int i, j, p, s;
    int k = n / m;
    int l = n % m;
    int h = (l == 0 ? k : k + 1);
    int flag;

    // pthread_t* threads = new pthread_t[h];
    // args_row* args = new args_row[h];

    for(p = 0; p < h; p++){
        get_block(A, block, n, m, p, p);
        flag = -1;
        flag = inverse(block, C, p != k ? m : l);
        if(flag == -1) return -1;
        set_block(A, block, n, m, p, p);
        for(s = p + 1; s < h; s++){
            get_block(A, block, n, m, p, s);
            multiply(C, block, dop_mat, p != k ? m : l, p != k ? m : l, p != k ? m : l, s != k ? m : l);
            set_block(A, dop_mat, n, m, p, s);
        }
        
        get_vector(B, X, n, m, p);
        multiply(C, X, dop_mat, p != k ? m : l, p != k ? m : l, p != k ? m : l, 1);
        set_vector(B, dop_mat, n, m, p);

        for(i = 0; i < h; i++){
            if(i == p) continue;
            get_block(A, block, n, m, i, p);
            for(j = p + 1; j < h; j++){
                
                get_block(A, C, n, m, p, j);
                multiply(block, C, dop_mat, (i != k ? m : l), m, m, (j != k ? m : l));
                get_block(A, C, n, m, i, j);
                subtract(C, dop_mat, (i != k ? m : l), (j != k ? m : l));
                set_block(A, C, n, m, i, j);
            }
            get_vector(B, X, n, m, p);
            multiply(block, X, dop_mat, (i != k ? m : l), p != k ? m : l, p != k ? m : l, 1);
            get_vector(B, X, n, m, i);
            subtract(X, dop_mat, (i != k ? m : l), 1);
            set_vector(B, X, n, m, i);
            get_block(A, block, n, m, i, p);
            zero(block, (i != k ? m : l), p != k ? m : l);
            set_block(A, block, n, m, i, p);
        }
    }

    for(i = 0; i < n; i++){
        X[i] = B[i];
    }

    return 1;
}
