#include <stdio.h>
#include <time.h>
#include <omp.h>
#define MAXTHREADS 8
long cantidadIntervalos = 10000000; //10 Million
double baseIntervalo;
//double acum = 0; //Can ́t be a shared variable
clock_t start, end;
void main() {
int THREADS = MAXTHREADS;
baseIntervalo = 1.0 / (double)cantidadIntervalos;
double x, partialSum[MAXTHREADS], totalSum = 0;
omp_set_num_threads(THREADS);
start = clock();
#pragma omp parallel
{
int numThread = omp_get_thread_num();
double acum = 0; // Can ́t be a shared variable, must be private to thread.
double fdx = 0; //Can ́t be a shared variable, must be private to thread.
for (long i = numThread; i < cantidadIntervalos; i += THREADS) {
x = i * baseIntervalo;
fdx = 4 / (1 + x * x);
acum += fdx;
}
acum *= baseIntervalo; //Multiply accumulated heights of the rectangles by the base size.
partialSum[numThread] = acum;
printf("Resultado parcial (Thread %d)\nacum = %lf\n", numThread, acum);
}
end = clock();
for (int c = 0; c < THREADS; c++)
totalSum += partialSum[c];
printf("\nResultado (%d threads) = %20.18lf (%ld)\n", THREADS, totalSum, 
end - start);
}