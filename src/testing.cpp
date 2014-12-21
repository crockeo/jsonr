//////////////
// Includes //
#include <iostream>

#include "testing/00.hpp"

//////////
// Code //

// The entry point to the testing suite.
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Proper usage: " << argv[0] << " <test number>." << std::endl;
        return 1;
    }

    int n = atoi(argv[1]);
    switch (n) {
    case 0:
        return runTest00();
        break;
    default:
        break;
    }

    std::cerr << "Invalid test number!" << std::endl;
    return 1;
}
