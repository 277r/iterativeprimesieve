#include <iostream>
#include <cmath>
#include <x86_64-linux-gnu/gmp.h>
#define SLS 20000
#define LOGLEVEL 1

int main(int argc, char* argv[]){

    if (argc < 2){
        return -1;
    }
    
    int x = std::stoi(argv[1]);  
    if ((x & 1) == 0 ) {
        std::cout << "ispriment";
        return -1;
    }
        // create list, set zero  
    bool *numArray_en = new bool[SLS];
    int *numArray = new int[SLS];
    for (int i = 0; i < SLS; i++){
        numArray[i] = 0;
        // zero is TRUE, 1 is FALSE, this could optimize since 'jz' faster than 'jnz'
        numArray_en[i] = 1;
    }
    numArray_en[3] = 0;

    int ROOT = std::sqrt(x) + 1;
     // zero is TRUE, 1 is FALSE, this could optimize since 'jz' faster than 'jnz'
    bool divisor = 1;


    for (int i = 3; i < ROOT; i += 2){
        divisor = 1;
        
        // iterate through list and increment each value that needs incrementing
        for (int j = 3; j < SLS; j++){
            if (numArray_en[j] == 0){
                numArray[j]++;
                // if divisor equals incremention, signal STOP, meaning non-prime
                if (numArray[j] == j){
                    divisor = 0;
                    numArray[j] = 0;
                }
            }

        }



#if LOGLEVEL > 4
        for (int k = 0; k < SLS; k++){
            std::cout << numArray[k] << ", ";

        }
        std::cout << "\n\n";
#endif

        if (divisor == 0){
            continue;
        }



        // DUURT LANG!!
        int j = x % i;
        if (j == 0){
            std::cout << "ISPRIMENT\n";
            return -1;
        }
        if (j != 0){
            numArray_en[i] = 0;
            numArray[i] = 0;
            continue;
        }

        


        

    }

    std:: cout << "NUM ISPRIME\n";

    

}