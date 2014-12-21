#include "00.hpp"

//////////////
// Includes //
#include <iostream>

#include "../parser.hpp"
#include "../json.hpp"

//////////
// Code //

// Running the test.
int runTest00() {
    JValue val = parseJSON("hello world");
    if (val.isNull())
        return 1;

    std::cout << val.jString() << std::endl;

    return 0;
}
