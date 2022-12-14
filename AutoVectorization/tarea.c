#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

// Single Threaded Array Addition FLOATs
int main() {
    int i;
    float* A = NULL;
    float* B = NULL;
    float* C = NULL;
    int result = 1;
    const int elements = 52428800;
    time_t start, end;

    //Array creation
    size_t datasize = sizeof(float) * elements;
    A = (float*)_mm_malloc(datasize, 16);
    B = (float*)_mm_malloc(datasize, 16);
    C = (float*)_mm_malloc(datasize, 16);
    
    //Array initialization (Normally you would get this from a file)
    for (i = 0; i < elements; i++) {
        A[i] = (float) i;
        B[i] = (float) i;
    }
    
    start = clock();
    
    //This loop can be optimized using Intrinsics
    for (i = 0; i < elements; i++)
        C[i] = A[i] + B[i];
    end = clock();
    
    //Validation
    for (i = 0; i < elements; i++) {
        if (C[i] != i + i) {
            result = 0;
            break;
        }
    }

    //Print first 10 results
    for (i = 0; i < 10; i++) {
        printf("C[%d]=%10.2lf\n", i, C[i]);
    }

    if (result) {
        printf("Results verified!!! (%ld)\n", (long)(end - 
            start));
    }

    else {
        printf("Wrong results!!!\n");
    }

    //Memory deallocation
    _mm_free(A);
    _mm_free(B);
    _mm_free(C);
    
    return 0;
}