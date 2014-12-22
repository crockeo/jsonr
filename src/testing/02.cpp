#include "02.hpp"

//////////////
// Includes //
#include "../parser.hpp"
#include "../json.hpp"
#include "utils.hpp"

//////////
// Code //

// Testing the parseJSON function for parsing a number.
int runTest02() {
    JValue positiveVal = parseJSON("12345");
    JValue negativeVal = parseJSON("-12345");
    JValue floatingPosVal = parseJSON("54321.12345");
    JValue floatingNegVal = parseJSON("-54321.12345");

    if (!positiveVal.isNumber() || !around(12345, positiveVal.jNumber(), 1))
        return 1;

    if (!negativeVal.isNumber() || !around(-12345, negativeVal.jNumber(), 1))
        return 1;

    if (!floatingPosVal.isNumber() || !around(54321.12345, floatingPosVal.jNumber(), 1))
        return 1;

    if (!floatingNegVal.isNumber() || !around(-54321.12345, floatingNegVal.jNumber(), 1))
        return 1;
    
    return 0;
}
