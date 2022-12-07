#include <stdio.h>
#include <omp.h> 

int main() {
    //omp_set_num_threads(1000000);
    
    #pragma omp parallel num_threads(30000)
    {
        if (omp_get_thread_num() == 0) {
            printf("Num threads = %d\n", omp_get_num_threads());
        }
        //printf("Num threads = %d\n", omp_get_num_threads());
    }
}