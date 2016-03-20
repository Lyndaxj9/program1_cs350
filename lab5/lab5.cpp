#include <iostream>
#include <stdlib.h>
#include <cstdlib>

int main(int argc, char* argv[]){
    int numFramem;
    const char* fileName;

    if(argc==3){
        numFramem = atoi(argv[1]);
        fileName = argv[2];
        std::cout<<"Using: "<<fileName<<" we have "<<numFramem<<" internal"
            <<" page table memory"<<std::endl;
    }else{
        std::cout<<"Incorrect Argument Amount"<<std::endl;
    }

    return 0;
}
