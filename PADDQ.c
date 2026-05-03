
#define __AVX2__
#define __SSE2__
#define __x86_64__
#define __MMX__
#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>
#include <immintrin.h>

void printArr(unsigned int* data){
    for (int i = 0; i < 8; i++){
        printf("%d, ", data[i]);
    }
    printf("\n");
}

// Supported: avx avx2 ht lm nx pae sse sse2 sse3 sse4_1 sse4_2 sse4a ssse3 svm

void main(){
    
    register unsigned int *counter_max asm("%mm1");
    register unsigned int *counter_val asm("%mm2");
    register unsigned int *increment asm("%mm3");
    counter_val = malloc(1024*sizeof(unsigned int));
    counter_max = malloc(1024*sizeof(unsigned int));
    increment = malloc(1024*sizeof(unsigned int));
    
    
    for (int i = 0; i < 8; i++){
        counter_val[i] = rand() % 256;
        counter_max[i] = counter_val[i] ;
        increment[i] = 1;
    }
    counter_val[2] = 2;
    counter_max[2] = 13;
    printArr(counter_val);
    printArr(increment);
    printArr(counter_max);
   
    __m256i valA, valB;


    valA = _mm256_loadu_si256(counter_val);
    /*
    valB = _mm256_loadu_si256(increment);
    valA = _mm256_add_epi32(valA, valB);
    
    _mm256_storeu_si256(counter_val, valA);
    */

    // compare with counter max
    valB =_mm256_loadu_si256(counter_max);
    

    // masked for numbers A == B
    __m256i inmax = _mm256_cmpeq_epi32(valA,valB);

    valA = _mm256_blendv_epi8(valA, _mm256_setzero_si256(), inmax);
    _mm256_storeu_si256(counter_val, valA);

    int cmp = 0;

    if (cmp)
    {
        printf("contains equal element %d\n", cmp);
    }
    else {
        printf("no equal element found%d\n", cmp);
    }
    for (int i = 0; i < 8; i++){
        printf("%d, ",   counter_val[i] );
    }
    
    
    
    /*
    register int *counter_val asm("%mm1");
    register int *increment asm("%mm2");
    counter_val = malloc(64*sizeof(int));
    increment = malloc(64*sizeof(int));
    
    for (int i = 0; i < 64; i++){
        counter_val[i] = rand() % 256;
        printf("%d, ", counter_val[i]);
        increment[i] = 1;
    }
    printf("\n");
    // use SSE2 instead of PADDQ? 
    __asm__("PXOR %mm1, %mm1\n");
    __asm__("PADDQ %mm1, %mm2\n");
    
    for (int i = 0; i < 64; i++){
        printf("%d, ",   counter_val[i] );
    }
    */
}