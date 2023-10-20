#include "jordan.h"
#include "funcs.h"
#include <iostream>

#define EPSILON 2.22507e-308

int Jordan(double *A, double *B, double *X, double *C, double *block, double *dop_mat, int n, int m){
    int i, j, p, q, s;
    int k = n / m;
    int l = n % m;
    int cur_i = 0;
    int h = (l == 0 ? k : k + 1);
    int flag;

    for(p = 0; p < k; p++){
        flag = -1;
        for(q = 0; q < k; q++){
            for(i = 0; i < p; i++){
                get_block(A, block, n, m, q, i);
                if(compare_with_zero(block, m) == -1){
                    flag = 0;
                    break;
                }
                else flag = -1;
            }
            if(flag == 0) continue;
            get_block(A, block, n, m, q, p);
            flag = inverse(block, C, m);
            if(flag == 1){
                cur_i = q;
                E(block, m);
                set_block(A, block, n, m, cur_i, p);
                for(s = p + 1; s < h; s++){
                    get_block(A, block, n, m, cur_i, s);
                    multiply(C, block, dop_mat, m, m, m, s != k ? m : l);
                    set_block(A, dop_mat, n, m, cur_i, s);
                }
                get_vector(B, X, n, m, cur_i);
                multiply(C, X, dop_mat, m, m, m, 1);
                set_vector(B, dop_mat, n, m, cur_i);
                break;
            }
        }
        if(flag == -1) return -1;
        for(i = 0; i < h; i++){
            if(cur_i == i) continue;
            get_block(A, block, n, m, i, p);
            for(j = p + 1; j < h; j++){
                get_block(A, C, n, m, cur_i, j);
                multiply(block, C, dop_mat, (i != k ? m : l), m, m, (j != k ? m : l));
                get_block(A, C, n, m, i, j);
                subtract(C, dop_mat, (i != k ? m : l), (j != k ? m : l));
                set_block(A, C, n, m, i, j);
            }
            get_block(A, block, n, m, i, p);
            get_vector(B, X, n, m, cur_i);
            multiply(block, X, dop_mat, (i != k ? m : l), m, m, 1);
            get_vector(B, X, n, m, i);
            subtract(X, dop_mat, (i != k ? m : l), 1);
            set_vector(B, X, n, m, i);
            get_block(A, block, n, m, i, p);
            zero(block, (i != k ? m : l), m);
            set_block(A, block, n, m, i, p);
        }
    }
    if(l != 0){
        get_block(A, block, n, m, k, k);
        flag = inverse(block, C, l);
        if(flag == -1) return -1;
        E(block, l);
        set_block(A, block, n, m, k, k);
        get_vector(B, X, n, m, k);
        multiply(C, X, dop_mat, l, l, l, 1);
        set_vector(B, dop_mat, n, m, k);
        for(i = 0; i < k; i++){
            get_block(A, block, n, m, i, k);
            get_vector(B, X, n, m, k);
            multiply(block, X, dop_mat, m, l, l, 1);
            get_vector(B, X, n, m, i);
            subtract(X, dop_mat, m, 1);
            set_vector(B, X, n, m, i);
            get_block(A, block, n, m, i, k);
            zero(block, m, l);
            set_block(A, block, n, m, i, k);
        }
    }
    for(i = 0; i < h; i++){
        for(j = 0; j < h; j++){
            get_block(A, block, n, m, i, j);
            if(!(block[0] < 1 - EPSILON || block[0] > 1 + EPSILON)){
                for(p = 0; p < m; p++){
                    X[j * m + p] = B[i * m + p];
                }
                break;   
            }
        }
    }
    return 1;
}