// gcc -mavx -march=native main.c -o main

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

#define AVX
//#define SSE

// Single Threaded Array Addition FLOATs

int main() {
	int i;
	float* A = NULL;
	float* B = NULL;
	float* C = NULL;
	int result = 1;
	const int elements = 52428800;
	time_t start, end;

	//Array creation
	size_t datasize = sizeof(float) * elements;
	#ifdef AVX
	A = (float*)_mm_malloc(datasize, 32);
	B = (float*)_mm_malloc(datasize, 32);
	C = (float*)_mm_malloc(datasize, 32);
	#elif defined(SSE)
	A = (float*)_mm_malloc(datasize, 16);
	B = (float*)_mm_malloc(datasize, 16);
	C = (float*)_mm_malloc(datasize, 16);
	#else // Make Sequential the default
	A = (float*)malloc(datasize);
	B = (float*)malloc(datasize);
	C = (float*)malloc(datasize);
	#endif

	//Array initialization (Normally you would get this from a file)
	for (i = 0; i < elements; i++) {
		A[i] = (float) i;
		B[i] = (float) i;
	}

	start = clock();
	// This loop can be optimized using Intrinsics
	#ifdef AVX
	for (i = 0; i < elements/8; i++) {
		__m256 a8 = _mm256_load_ps(A+(i*8));
		__m256 b8 = _mm256_load_ps(B+(i*8));
		__m256 sum8 = _mm256_add_ps(a8, b8);
		_mm256_store_ps(C+(i*8), sum8);
	}
	#elif defined(SSE)
	for (i = 0; i < elements/4; i++) {
		__m128 a4 = _mm_load_ps(A+(i*4));
		__m128 b4 = _mm_load_ps(B+(i*4));
		__m128 sum4 = _mm_add_ps(a4, b4);
		_mm_store_ps(C+(i*4), sum4);
	}
	#else
	for (i = 0; i < elements; i++)
		C[i] = A[i] + B[i];
	#endif
	end = clock();

	//Validation
	for (i = 0; i < elements; i++) {
		if (C[i] != i + i) {
			result = 0;
			break;
		}
	}

	//Print first 10 results
	for (i = 0; i < 10; i++) {
		printf("C[%d]=%10.2lf\n", i, C[i]);
	}

	if (result) {
		printf("Results verified!!! (%ld)\n", (long)(end - start));
	}
	else {
		printf("Wrong results!!!\n");
	}

	//Memory deallocation
	#ifdef AVX
	_mm_free(A);
	_mm_free(B);
	_mm_free(C);
	#elif defined(SSE)
	_mm_free(A);
	_mm_free(B);
	_mm_free(C);
	#else // Make Sequential the default
	free(A);
	free(B);
	free(C);
	#endif

	return 0;
}