#include <stdio.h>
#include <omp.h>

int main(int argc, char const *argv[])
{
    // 201511 -> 4.5
    printf("Version OMP: %d\n", _OPENMP);
    return 0;
}
