#ifndef FUNCTIONS
#define FUNCTIONS

void set_block (double *A, double *block, int n, int m, int i, int j);

void get_block (double *A, double *block, int n, int m, int i, int j);

void set_vector(double *A, double *vector, int n, int m, int i);

void get_vector(double *A, double *vector, int n, int m, int i);

double f(int s, int n, int i, int j);

double get_r1(double *A, double *X, double *B, int n);

double get_r2(double *X, int n);

void multiply(double *A, double *B, double *C, int rows_a, int cols_a, int rows_b, int cols_b);

void subtract(double *A, double *B, int n, int m);

int inverse(double *A, double *C, int n);

void get_free_memb(double *A, double *B, int n);

double det(double *A, int n);

int max(int i, int j);

int absolute(int i);

double absolute(double i);

void E(double *A, int n);

void zero(double *A, int n, int m);

int compare_with_zero(double *A, int n);

#endif