#include <iostream>

//#include "assembler/assembler.h"

int main(int argc, char* argv[]) {

    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }
    
    // std::cout << "\nPress any key to exit..." << std::endl;
    // std::cin.get();
    // ^^ uncomment this if being run in a seperate terminal

    return 0;
}