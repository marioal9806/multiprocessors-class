// gcc task_decomposition.c -o task_decomposition -fopenmp

#include <stdio.h>
#include <omp.h>

int main(int argc, char const *argv[])
{
    float A[16];
    float B[16];
    float C[16], D[16], E[16], F[16];

    for(int i = 0; i < 16; i++) {
        A[i] = i + 10.0;
        B[i] = i + 1.0;
        C[i] = D[i] = E[i] = F[i] = 0;
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i = 0; i < 16; i++)
            {
                C[i] = A[i] + B[i];                
            }
        }
        #pragma omp section
        {
            for (int i = 0; i < 16; i++)
            {
                D[i] = A[i] - B[i];
            }
        }
        #pragma omp section
        {
            for (int i = 0; i < 16; i++)
            {
                E[i] = A[i] * B[i];
            }
        }
        #pragma omp section
        {
            for (int i = 0; i < 16; i++)
            {
                F[i] = A[i] / B[i];
            }
        }
    }
    
    printf("C: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%f ", C[i]);
    }
    printf("\n");
    
    printf("D: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%f ", D[i]);
    }
    printf("\n");

    printf("E: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%f ", E[i]);
    }
    printf("\n");

    printf("F: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%f ", F[i]);
    }
    printf("\n");

    return 0;




    
}
