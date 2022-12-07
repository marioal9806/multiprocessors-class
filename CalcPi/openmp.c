// gcc -fopenmp openmp.c -o openmp
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define NUM_THREADS 12

long cantidadIntervalos = 1000000000;
double baseIntervalo;
double cantIntPorThread;

double acum[NUM_THREADS];

clock_t start, end;

void main() {
    baseIntervalo = 1.0 / cantidadIntervalos;
    cantIntPorThread = cantidadIntervalos / (double)NUM_THREADS;

    start = clock();

    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        #pragma omp single
        printf("Threads received from kernel: %d\n", omp_get_num_threads());
    }

    #pragma omp parallel
    {
        long i;
        int thread_id = omp_get_thread_num();
        double fdx, x;
        double localAcum = 0;
        x = cantIntPorThread * baseIntervalo * (double)thread_id;
        for (i = 0; i < cantIntPorThread; i++) {
            fdx = 4 / (1 + x * x);
            localAcum = localAcum + (fdx * baseIntervalo);
            x = x + baseIntervalo;
        }

        acum[thread_id] = localAcum;
    }
    
    double total = 0;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        total += acum[i];
    }

    end = clock();
    printf("Resultado = %20.18lf (%ld)\n", total, end - start);
}