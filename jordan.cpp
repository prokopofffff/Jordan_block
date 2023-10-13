#include "jordan.h"
#include "funcs.h"

int Jordan(double *A, double *B, double *X, double *C, double *block, double *dop_mat, int n, int m){
    int i, j, p, q, s;
    int k = n / m;
    int l = n % m;
    int cur_i;
    int h = (l != 0 ? k : k + 1);
    int flag;

    for(p = 0; p < (l != 0 ? k : k - 1); p++){
        flag = -1;
        for(q = 0; q < (l != 0 ? k : k - 1); q++){
            get_block(A, block, n, m, q, p);
            flag = inverse(block, C, m, m);
            if(flag == 1){
                cur_i = q;
                E(block, m);
                set_block(A, block, n, m, q, p);
                for(s = p + 1; s < h; s++){
                    get_block(A, block, n, m, cur_i, s);
                    multiply(C, block, dop_mat, m, m, m, s != k ? m : l);
                    set_block(A, dop_mat, n, m, q, s);
                }
                get_vector(B, block, n, m, q);
                multiply(C, block, dop_mat, m, m, m, 1);
                set_vector(B, dop_mat, n, m, q);
                break;
            }
        }
        if(flag == -1) return 0;
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
            get_vector(B, C, n, m, cur_i);
            multiply(block, C, dop_mat, (i != k ? m : l), m, m, 1);
            get_vector(B, C, n, m, i);
            subtract(C, dop_mat, (i != k ? m : l), 1);
            set_vector(B, C, n, m, i);
            get_block(A, block, n, m, i, p);
            zero(block, (i != k ? m : l), m);
            set_block(A, block, n, m, i, p);
        }
    }
    if(l != 0){
        get_block(A, block, n, m, k + 1, k + 1);
        flag = inverse(block, C, l, l);
        if(flag == -1) return 0;
        E(block, l);
        set_block(A, block, n, m, k + 1, k + 1);
        multiply(C, block, dop_mat, l, l, l, l);
        set_block(A, dop_mat, n, m, k + 1, k + 1);
        get_vector(B, block, n, m, k + 1);
        multiply(C, block, dop_mat, l, l, l, 1);
        set_vector(B, dop_mat, n, m, k + 1);
        for(i = 0; i < k; i++){
            get_block(A, block, n, m, i, k + 1);
            get_vector(B, C, n, m, k + 1);
            multiply(block, C, dop_mat, m, l, l, 1);
            get_vector(B, C, n, m, i);
            subtract(C, dop_mat, m, 1);
            set_vector(B, C, n, m, i);
            get_block(A, block, n, m, i, k + 1);
            zero(block, m, l);
            set_block(A, block, n, m, i, k + 1);
        }
    }
    for(i = 0; i < k; i++){
        for(j = 0; j < k; j++){
            get_block(A, block, n, m, i, j);
            if(block[0] == 1){
                X[j] = B[i];
                break;    
            }
        }
    }
    return 1;
}