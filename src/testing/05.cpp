#include "05.hpp"

//////////////
// Includes //
#include "../parser.hpp"
#include "../json.hpp"

//////////
// Code //

#include <iostream>

// Testing the simple object.
bool testSimpleObject(JValue simpleObject) {
    if (!simpleObject.isObject())
        return true;

    std::map<std::string, JValue> map = simpleObject.jObject();

    std::cout << "YIS.\n";

    if (map.count("test") == 0)
        return true;

    std::cout << "YIS.\n";

    if (!map["test"].isBool())
        return true;

    std::cout << "YIS.\n";

    if (map["test"].jBool() != true)
        return true;

    return false;
}

// Attempting to test parseJSON for 'null' values.
int runTest05() {
    JValue simpleObject = parseJSON("{ \"test\": true }");

    if (testSimpleObject(simpleObject))
        return 1;

    return 0;
}
