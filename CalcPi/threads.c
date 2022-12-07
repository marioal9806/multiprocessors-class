// gcc -pthread threads.c -o threads
#include <stdio.h>
#include <time.h>
#include <pthread.h>

long cantidadIntervalos = 1000000000;
double baseIntervalo;
double cantIntPorThread;
double acum = 0;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void* thread_routine(void* arg) {
    double* param = (double*)arg;
    double fdx, x;
    double localAcum = 0;
    long i;
    
    x = cantIntPorThread * baseIntervalo * (*param);
    for (i = 0; i < cantIntPorThread; i++) {
        fdx = 4 / (1 + x * x);
        localAcum = localAcum + (fdx * baseIntervalo);
        x = x + baseIntervalo;
    }

    pthread_mutex_lock(&mutex1);
    acum += localAcum;
    pthread_mutex_unlock(&mutex1);
}

int main() {
    clock_t start, end;
    double x;
    long i;

    const int numThreads = 12;
 
    double param[numThreads];
    pthread_t hThread[numThreads];

    baseIntervalo = 1.0 / cantidadIntervalos;
    cantIntPorThread = cantidadIntervalos / (double)numThreads;

    start = clock();

    for (int i = 0; i < numThreads; i++)
    {
        param[i] = i;
        pthread_create(&hThread[i], NULL, thread_routine, &param[i]);
    }
    
    for (int i = 0; i < numThreads; i++)
    {
        pthread_join(hThread[i], NULL);
    }
    
    end = clock();

    printf("Resultado = %20.18lf (%ld)\n", acum, end - start);
    pthread_mutex_destroy(&mutex1);
    
    return 0;
}