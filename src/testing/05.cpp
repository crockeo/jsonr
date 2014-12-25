#include "05.hpp"

//////////////
// Includes //
#include "../parser.hpp"
#include "../json.hpp"

//////////
// Code //

// Testing the simple object.
bool testSimpleObject(JValue simpleObject) {
    if (!simpleObject.isObject())
        return true;

    std::map<std::string, JValue> map = simpleObject.jObject();

    if (map.count("test") == 0)
        return true;

    if (!map["test"].isBool())
        return true;

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
