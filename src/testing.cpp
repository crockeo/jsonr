//////////////
// Includes //
#include <iostream>

//////////
// Code //

// The entry point to the testing suite.
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Proper usage: " << argv[0] << " <test number>" << std::endl;
        return 1;
    }

    return 0;
}
