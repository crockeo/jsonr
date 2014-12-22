#include "00.hpp"

//////////////
// Includes //
#include <iostream>

#include "../parser.hpp"
#include "../json.hpp"

//////////
// Code //

// Testing the parseJSON function for parsing a boolean.
int runTest00() {
    JValue tVal = parseJSON("true");
    JValue fVal = parseJSON("false");

    if (tVal.isBool() && fVal.isBool() &&
        tVal.jBool() && !fVal.jBool()) {
        return 0;
    }

    return 1;
}
