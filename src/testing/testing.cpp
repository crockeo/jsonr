//////////////
// Includes //
#include <iostream>

#include "00.hpp"
#include "01.hpp"
#include "02.hpp"
#include "03.hpp"
#include "04.hpp"
#include "05.hpp"

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
    case 1:
        return runTest01();
    case 2:
        return runTest02();
    case 3:
        return runTest03();
    case 4:
        return runTest04();
    case 5:
        return runTest05();
    default:
        break;
    }

    std::cerr << "Invalid test number!" << std::endl;
    return 1;
}
