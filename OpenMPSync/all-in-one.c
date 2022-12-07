#include <stdio.h>
#include <time.h>
long cantidadIntervalos = 1000000000;
double baseIntervalo;
double acum = 0;
clock_t start, end;

void main() {
    long i;
    baseIntervalo = 1.0 / cantidadIntervalos;
    double x;
    double fdx;
    
    start = clock();

    #pragma omp parallel for private (fdx,x,i) reduction(+:acum)
    for (i = 0; i < cantidadIntervalos; i++) {
        x = (i+0.5) * baseIntervalo;
        fdx = 4 / (1 + x * x);
        acum += fdx;
    }
    acum *= baseIntervalo;
    
    end = clock();
    printf("Resultado = %20.18lf (%ld)\n", acum, end - start);
}

