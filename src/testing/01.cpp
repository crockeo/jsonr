#include "01.hpp"

//////////////
// Includes //
#include "../jsonr/parser.hpp"
#include "../jsonr/json.hpp"

//////////
// Code //

using namespace jsonr;

// Testing the parseJSON function for parsing a string.
int runTest01() {
    JValue sVal = parseJSON("\"hello\"");
    JValue sqVal = parseJSON("\"word up\"");
    JValue midVal = parseJSON("\"with mid \\\" quotes!!!\"");

    if (sVal.isString() && sVal.jString().compare("hello") == 0 &&
        sqVal.isString() && sqVal.jString().compare("word up") == 0 &&
        midVal.isString() && midVal.jString().compare("with mid \" quotes!!!") == 0)
        return 0;

    return 1;
}
