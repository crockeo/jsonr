#include "01.hpp"

//////////////
// Includes //
#include "../parser.hpp"
#include "../json.hpp"

//////////
// Code //

// Testing the parseJSON function for parsing a string.
int runTest01() {
    JValue sVal = parseJSON("\"hello\"");
    JValue sqVal = parseJSON("'word up'");

    if (sVal.isString() && sVal.jString().compare("hello") == 0 &&
        sqVal.isString() && sqVal.jString().compare("word up") == 0)
        return 0;

    return 1;
}
