#include "03.hpp"

//////////////
// Includes //
#include <vector>

#include "../parser.hpp"
#include "../json.hpp"
#include "utils.hpp"

//////////
// Code //

// Testing the number array.
bool testNumArray(JValue numArray) {
    if (!numArray.isArray())
        return true;
    std::vector<JValue> vals = numArray.jArray();

    for (int i = 0; i < vals.size(); i++)
        if (!vals[i].isNumber() || !around((double)(i + 1), vals[i].jNumber(), 1))
            return true;

    return false;
}

// Testing the string array.
bool testStrArray(JValue strArray) {
    return false;
}

// Testing the bool array.
bool testBoolArray(JValue boolArray) {
    return false;
}

// Testing the Array portion of parseJSON.
int runTest03() {
    JValue numArray  = parseJSON("[1, 2, 3, 4, 5]");
    JValue strArray  = parseJSON("[\"testing\", \"with spaces\", \"and a 'quote\"]");
    JValue boolArray = parseJSON("[true, false, true]");

    if (testNumArray(numArray))
        return 1;
    if (testStrArray(strArray))
        return 1;
    if (testBoolArray(boolArray))
        return 1;

    return 0;
}
