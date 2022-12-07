// gcc -mavx -march=native exercise1.c -o exercise1

#include <x86intrin.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int array0[8] __attribute__((aligned(32)));
    __m256i a8 = _mm256_set_epi32(75,65,51,86,65,-212,0,44);
    __m256i b8 = _mm256_set_epi32(-85,35,4,-86,-60,220,4,31);
    __m256i sum8 = _mm256_add_epi32(a8, b8);
    //__assume_algined(array0, 32);
    _mm256_store_si256((__m256i*)&array0, sum8);
    
    for (int i = 0; i < 8; i++)
    {
        printf("%d\n", array0[i]);
    }

    return 0;
}
