#include "nextPrime.cpp"
#include <thread>
#include <unistd.h>

NP_num *DONE;


void divide(NP_num *a, NP_iterator *_b){ 
    NP_num b = (unsigned long long)(*_b); 

    if (*a == 0 || b == 0){
        return;
    }
    if (((*a) % (b)) == 0){
        std::cout << "DIVIDER FROM " << *a << "DIVISIBLE BY" << b << std::endl;
    }
    return;
}

void repGetNext(PrimeSieve *j){
    // dont overflow
    while (j->getListSize() < j->getMaxListSize()){
        j->getNextSet();
    }
    std::cout << "maxlistSize overflow" << "\n";
    (*DONE)++;
    std::cout.flush();
    return;
}

// offset, increment integers
void try_i(NP_num *src,PrimeSieve *j, int off, int inc){
    // no need to go above ULL, indexing can't be bigger
    unsigned long long index = off;
    while (true){
        divide(src,j->getNum(index));
        index += inc;
        while (index >= j->getListSize()){
            usleep(50);
        }
    }
}



int main(int argc, char*argv[]){
    NP_num *x = new NP_num;
    (*x) = std::stoull(argv[1]);
    int threadcount = std::stoi(argv[2]);
    
    // on the heap so that threads can access
    PrimeSieve *j = new PrimeSieve(100000, 0);
    std::thread inc = std::thread(repGetNext, j);
    DONE = new NP_num;
    *DONE = 0;

    std::thread *threads = new std::thread[threadcount];
    for (int i = 0; i < threadcount; i++){
        threads[i] = std::thread(try_i,x,j, i, threadcount);
    }
    // do nothing?
    while (true){
        usleep(100000);
        if (*DONE == 1){
            return 0;
        }
    }

    return 0;

}

