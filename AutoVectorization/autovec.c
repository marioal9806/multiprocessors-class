// gcc autovec.c -o autovec -O -ftree-vectorize -mavx2 -fopt-info-vec-missed -fopt-info-vec
// gdb -q ./autovec
// disassemble <function to disassemble>
// quit
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024

int main() {
    // Si no está alineado, no autovectoriza :p
    int A[SIZE] __attribute__((aligned(32)));
    int B[SIZE] __attribute__((aligned(32)));

    for (int i = 0; i < SIZE; i++)
        A[i] = B[i] = i;

    // This loop will be auto-vectorized
    for (int i = 0; i < SIZE; i++)
        A[i] = A[i] + B[i];
    
    for (int i = 0; i < 1024; i++)
        printf("%2d %2d %2d\n", i, A[i], B[i]);
    
    return 0;
}