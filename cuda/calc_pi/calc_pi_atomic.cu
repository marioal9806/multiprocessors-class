// nvcc -arch=sm_60 calc_pi.cu -o calc_pi

#include <stdio.h>
#include <time.h>

clock_t start, end;

__global__ void calc_pi_kernel(long n, double* acum) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    int stride = gridDim.x * blockDim.x;
    
    double x = 0;
    double fdx = 0;
    double baseIntervalo = 1.0 / n;

    double localAcum = 0;

    for (long i = index; i < n; i += stride) {
        x = (i+0.5)*baseIntervalo;
        fdx = 4 / (1 + x * x);
        localAcum += fdx;
    }
    atomicAdd(acum, localAcum);
}

int main() {
    
    double *acum;
    int size = sizeof(double);

    long cantidadIntervalos = 1000000000;
    double baseIntervalo = 1.0 / cantidadIntervalos;

    // Definir el numero de threads a utilizar en el device
    int blockSize = 1024;
    int numBlocks = 16384;

    // Asignar un acumulador local para cada thread
    int ret = 0;
    ret = cudaMallocManaged((void **)&acum, size);
    if (ret) {
        printf("Error on CUDA Malloc: %d\n", ret);
    }
    
    cudaMemset(acum, 0, size);

    start = clock();
    calc_pi_kernel<<<numBlocks, blockSize>>>(cantidadIntervalos, acum);
    cudaDeviceSynchronize();
    end = clock();

    *acum *= baseIntervalo; 

    printf("Result = %20.18lf (%ld)\n", *acum, end - start);

    cudaFree(acum);

    return 0;
}