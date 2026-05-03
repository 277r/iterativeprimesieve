// Implementation of prime sieve in a class, with a getNext 
// 0: none
// 1: errors
// 2: warnings
// 3: information
// 4: verbose
#define NP_LOGLEVEL 3
#if NP_LOGLEVEL > 0
#include <iostream>
#ifndef __AVX2__
#define __AVX2__
#endif
#ifndef __SSE2__
#define __SSE2__
#endif
#ifndef __x86_64__
#define __x86_64__
#endif
#ifndef __MMX__
#define __MMX__
#endif

#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>
#include <immintrin.h>
#endif

#define NP_num unsigned int
#define NP_iterator unsigned int



class PrimeSieve{
private:

    // if zero, no increments will occur
    // list increment size in pointers should be seen as 1024^(listInc)
    int listInc;
    int threads;
    
    NP_num currentNum = 3;

    NP_iterator numlistIndex;
    NP_iterator maxListSize;
    // contain the actual list
    NP_iterator *numArray_max; 
    NP_iterator *numArray;
    NP_iterator increment[8] __attribute__ ((aligned (32))) = {1, 1, 1, 1, 1, 1, 1, 1};
    
    
    public:
    NP_iterator *getNum(int index){
        return &(numArray_max[index]);
    }
    NP_iterator getListSize(){
        return numlistIndex;
    }
    NP_iterator getMaxListSize(){
        return maxListSize;
    }

    // external accesibility should improve since less copies are made, be careful when porting to gmp types
    NP_iterator primeSet;
    __m256i valA, valB, valINC;

    // first argument can be ignored if listInc is non-zero
    PrimeSieve(NP_iterator _maxListSize, int _listInc){
        // fix logleveleing
        #if NP_LOGLEVEL > 2
        printf("Size of num, size of iterator resp.: %d, %d\n", sizeof(NP_num), sizeof(NP_iterator));
        #endif

        maxListSize = _maxListSize;
        listInc = _listInc;
        if (_listInc == 0){
            numArray_max = (NP_num*) _mm_malloc(_maxListSize*sizeof(NP_num),sizeof(NP_num)*8);
            numArray = (NP_iterator*) _mm_malloc(_maxListSize*sizeof(NP_iterator),sizeof(NP_iterator)*8);
        }

        // set to zero
        for (unsigned long long i = 0; i < _maxListSize; i++){
            numArray[i] = 0;
            numArray_max[i] = 0;
        }
        numlistIndex = 0;
        currentNum = 3;
        // init completed
        #if NP_LOGLEVEL > 2
        // clear buffer too
        std::cout << "memsetting init complete\n" << std::endl;
        #endif

    }
    // todo: delete[] all
    ~PrimeSieve(){
        
    }

    // unsafe function, can segfault if numListIndex is incremented above maxListSize.
    // can be avoided by getting primes only up to 2N where N is listsize. For less conservative estimations use pi(N) = 2/(ln N) 
    // memory safety costs time
    void getNextSet(){
        bool divisor = 1;
        

        
        
        // eight WORDS per batch
        unsigned long long segmentedIndex = numlistIndex >> 3;
        unsigned long long remIndex = numlistIndex & 7;
        // value constant throughout loop
        valINC = _mm256_load_si256((__m256i_u*)increment);

        // iterate through list and increment each value that needs incrementing, compare to max value, if equal, set to zero and set divisor to true 
        for (unsigned long long j = 0; j < segmentedIndex; j++){
            valA = _mm256_load_si256((__m256i_u*)&(numArray[8*j]));
            valA = _mm256_add_epi32(valA, valINC);

            // load numarray_max section
            valB = _mm256_load_si256((__m256i_u*)&(numArray_max[8*j]));
             // create mask, if numarray[.] == numarray_max[.] 
            __m256i inmax = _mm256_cmpeq_epi32(valA,valB);
            // if equal, set to zero (occurs at counter overflow)
            valA = _mm256_blendv_epi8(valA, _mm256_setzero_si256(), inmax);
            _mm256_store_si256((__m256i_u*)&(numArray[8*j]), valA);
            // test MASK, if MASK enabled
            if (!_mm256_testz_si256(inmax,inmax)){
                divisor = 0;
            }

        }
        for (unsigned long long j = 0; j < remIndex; j++){
            numArray[numlistIndex - 1 - j]++;
            if (numArray[numlistIndex - 1 - j] == numArray_max[numlistIndex - 1 - j]){
                    divisor = 0;
                    numArray[numlistIndex - 1 - j] = 0;
                }
        }



        


        #if NP_LOGLEVEL > 4
            std::cout << currentNum;
            std::cout << "\n\n\n";
        #endif
        // not a new divisor, increment and return
        if (divisor == 0){
            primeSet = 0;
            currentNum+= 2;
            return;
        }

        if (divisor == 1){
            #if NP_LOGLEVEL > 3
            std::cout << "new prime found:" << currentNum << "\n";
            #endif
     
            numArray[numlistIndex] = 0;
            numArray_max[numlistIndex] = currentNum;
            numlistIndex++;
            primeSet = currentNum;
            currentNum+= 2;
            return;
        }
    }

};


