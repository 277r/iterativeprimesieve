// multithreading this program could suck, maybe the program retrieving primes from this program could be multithreaded

#include "nextPrime.cpp"
#include <iostream>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char* argv[]){
    if (argc < 3){
        return -1;
    }
    int ls = std::stoull(argv[1]);
    int itmax = std::stoull(argv[2]);

    PrimeSieve x( 0, 1);
    for (int i = 0; i < itmax; i++){

        x.getNextSet();
    }
    // make sure to get a prime instead of a zero
    while (x.primeSet == 0){
        x.getNextSet();
    }
    
    std::cout << x.primeSet << "\n"; 

    clock_t start, t1,t2;
    start = clock();
    x.getNextSet();
    t1 = clock();
    while (x.primeSet == 0){
        x.getNextSet();
    }
    t2 = clock();
    float time1, time2;
    time1 = double(t1 - start)/ CLOCKS_PER_SEC;
    time2 = double(t2 - start)/ CLOCKS_PER_SEC;
    std::cout << x.primeSet << "nextprime\nsingle: " << time1 << ", inc: " << time2 << "\n\n"; 
}