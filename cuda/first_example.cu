#include <stdio.h>

__global__ void c_hello() {
    printf("Hello from cuda!\n");
}

int main(int argc, char const *argv[])
{
    c_hello<<<1, 1>>>();
    cudaDeviceSynchronize();
    return 0;
}
