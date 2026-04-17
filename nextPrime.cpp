// Implementation of prime sieve in a class, with a getNext 
// 0: none
// 1: errors
// 2: warnings
// 3: information
// 4: verbose
#define NP_LOGLEVEL 3
#if NP_LOGLEVEL > 0
#include <iostream>
#endif

#define NP_num unsigned long long



class PrimeSieve{
private:

    // if zero, no increments will occur
    // list increment size in pointers should be seen as 1024^(listInc)
    int listInc;
    int threads;
    
    NP_num currentNum = 3;

    NP_num numlistIndex;
    NP_num maxListSize;
    // contain the actual list
    NP_num *numArray_max; 
    NP_num *numArray;
    
    
    public:
    NP_num *getNum(int index){
        return &(numArray_max[index]);
    }
    NP_num getListSize(){
        return numlistIndex;
    }
    NP_num getMaxListSize(){
        return maxListSize;
    }

    // external accesibility should improve since less copies are made, be careful when porting to gmp types
    NP_num primeSet;

    // first argument can be ignored if listInc is non-zero
    PrimeSieve(NP_num _maxListSize, int _listInc){
        maxListSize = _maxListSize;
        listInc = _listInc;
        if (_listInc == 0){
            numArray_max = new NP_num[_maxListSize];
            numArray = new NP_num[_maxListSize];
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
        
        // iterate through list and increment each value that needs incrementing
        for (unsigned long long j = 0; j < numlistIndex; j++){
                numArray[j]++;
                // if divisor equals incremention, signal STOP, meaning non-prime
                if (numArray[j] == numArray_max[j]){
                    divisor = 0;
                    numArray[j] = 0;
                }

        }


        #if NP_LOGLEVEL > 3
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


