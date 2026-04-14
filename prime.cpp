// Author: RS
// To Do:   
//          remove division at end stage if possible, might require square root(num_in) to become num_in, squaring the amount of numbers (and because of nested for loop) time increase of 80dB / dec. Using the final divisor stage requires SQRT(N)*LOG(N) time since each number needs to be checked, check if feasible and avoidable
//     
// Done:
//          change SLS to be entered in program
//          Change list to only contain counters (use sets of index matched maxes and counters?) to improve memory, should have processor perfomance effect as well
// Optional:
//          Change SLS to variable list size with increment size steps, to automatically utilize more memory if more needed, would require realloc
#include <iostream>
#include <cmath>
#include <x86_64-linux-gnu/gmp.h>
#define LOGLEVEL 1


int main(int argc, char* argv[]){

    if (argc < 3){
        return -1;
    }
    
    unsigned long long x = std::stoull(argv[1]);  
    unsigned long long SLS = std::stoull(argv[2]);  
    if ((x & 1) == 0 ) {
        std::cout << "ispriment";
        return -1;
    }
    int numlistIndex = 0;
    // create list, set zero  
    unsigned long long *numArray_max = new unsigned long long[SLS];
    unsigned long long *numArray = new unsigned long long[SLS];



    for (unsigned long long i = 0; i < SLS; i++){
        numArray[i] = 0;
        numArray_max[i] = 0;
    }



    // do not count to ROOT, maybe?
    unsigned long long ROOT = sqrt(x) + 1;


     // zero is TRUE, 1 is FALSE, this could optimize since 'jz' faster than 'jnz'
    bool divisor = 1;


    for (unsigned long long i = 3; i < ROOT; i += 2){
        divisor = 1;
        
        // iterate through list and increment each value that needs incrementing
        for (unsigned long long j = 0; j < numlistIndex; j++){
                numArray[j]++;
                // if divisor equals incremention, signal STOP, meaning non-prime
                if (numArray[j] == numArray_max[j]){
                    divisor = 0;
                    numArray[j] = 0;
                }

        }


        #if LOGLEVEL > 4
        for (unsigned long long k = 0; k < SLS; k++){
            std::cout << numArray_max[k] << ", ";

        }
        std::cout << "\n";

        for (unsigned long long k = 0; k < SLS; k++){
            std::cout << numArray[k] << ", ";

        }
        std::cout << "\n\n\n";
        #endif

        if (divisor == 0){
            continue;
        }

        if (divisor == 1){
            #if LOGLEVEL > 4
            std::cout << "new prime found:" << i << "\n";
            #endif
     
            numArray[numlistIndex] = 0;
            numArray_max[numlistIndex] = i;
            numlistIndex++;
            continue;
        }
    }   
    // could be moved to the if(divisor == 1) section to improve non-prime performanc,e but hope to remove it
    std::cout << numlistIndex << "VNLS\n";
    for (int i = 0; i < numlistIndex; i++){
       if (x % numArray_max[i] == 0){
            std::cout << "NOT PRIME\n";
            return -1; 
        }
    }
    std:: cout << "NUM ISPRIME\n";
    return 0;

    

}