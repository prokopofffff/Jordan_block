#include "funcs.h"
#include "matrix.h"
#include "jordan.h"
#include <iostream>
#include <ctime>

int main(int argc, char* argv[]){
    try{

        if(argc != 5 && argc != 6){
            throw "Incorrect input";
            return -1;
        }

        int n = atoi(argv[1]), m = atoi(argv[2]), r = atoi(argv[3]), s = atoi(argv[4]);
        char *filename;
        double *A = new double[n * n];

        if(s == 0){
            filename = argv[5];
            matrix_input(filename, A, n);
        }
        else{
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    A[i * n + j] = f(s, n, i, j);
                    if(s != 1 && s != 2 && s != 3 && s != 4){
                        delete[] A;
                        throw "Undefined behaivor";
                        return -1;
                    }
                }
            }
        }

        matrix_output(A, n, n, r);

        double *B = new double[n];
        double *X = new double[n];
        double *block = new double[m * m];
        double *C = new double[m * m];
        double *dop_mat = new double[m * m];

        get_free_memb(A, B, n);
        
        double start1 = clock();
        int flag = Jordan(A, B, X, C, block, dop_mat, n, m);
        double end1 = clock();
        double t1 = (end1 - start1) / CLOCKS_PER_SEC;

        double t2 = 0;
        double r1 = -1;
        double r2 = -1;
        if(flag == 1){
            std::cout << std::endl;
            matrix_output(X, 1, n, r);
            std::cout << std::endl;
            double start2 = clock();
            r1 = get_r1(A, X, B, n);
            r2 = get_r2(X, n);
            double end2 = clock();
            t2 = (end2 - start2) / CLOCKS_PER_SEC;
        }

        int task = 7;
        printf("%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d M = %d\n", 
        argv[0], task, r1, r2, t1, t2, s, n, m);

        delete[] A;
        delete[] B;
        delete[] X;
        delete[] block;
        delete[] C;
        delete[] dop_mat;
    }
    catch(const char *err){
        std::cerr << err;
    }

}
