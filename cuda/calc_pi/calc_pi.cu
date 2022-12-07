// nvcc calc_pi.cu -o calc_pi

#include <stdio.h>
#include <time.h>

clock_t start, end;

__global__ void calc_pi_kernel(long n, double* acum) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    int stride = gridDim.x * blockDim.x;
    
    double x = 0;
    double fdx = 0;
    double baseIntervalo = 1.0 / n;

    for (long i = index; i < n; i += stride) {
        x = (i+0.5)*baseIntervalo;
        fdx = 4 / (1 + x * x);
        acum[index] += fdx;
    }
}

int main() {
    
    double *d_acum;
    double* h_acum;
    int size = sizeof(double);

    long h_cantidadIntervalos = 1000000000;
    double baseIntervalo = 1.0 / h_cantidadIntervalos;

    // Definir el numero de threads a utilizar en el device
    int blockSize = 1024;
    int numBlocks = 16384;
    int numThreads = blockSize*numBlocks;

    // Asignar un acumulador local para cada thread
    int ret = 0;
    ret = cudaMalloc((void **)&d_acum, size*numThreads);
    if (ret) {
        printf("Error on CUDA Malloc: %d\n", ret);
    }
    
    h_acum = (double*)malloc(size*numThreads);
    if (h_acum == NULL) {
        printf("Error on malloc\n");
    }

    start = clock();
    calc_pi_kernel<<<numBlocks, blockSize>>>(h_cantidadIntervalos, d_acum);
    cudaDeviceSynchronize();
    end = clock();

    // Get individual results back from device
    cudaMemcpy(h_acum, d_acum, size*numThreads, cudaMemcpyDeviceToHost);
    
    // Reduce final result on the host
    double acum_total = 0;
    for (int i = 0; i < numThreads; i++) {
        acum_total += h_acum[i];
    }
    acum_total *= baseIntervalo;

    printf("Result = %20.18lf (%ld)\n", acum_total, end - start);

    cudaFree(d_acum);
    free(h_acum);

    return 0;
}