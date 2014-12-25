#include "05.hpp"

//////////////
// Includes //
#include "../parser.hpp"
#include "../json.hpp"

//////////
// Code //

// Testing the empty object.
bool testEmptyObject(JValue emptyObject) {
    if (!emptyObject.isObject())
        return true;

    auto map = emptyObject.jObject();
    int n = 0;

    for (auto it = map.begin(); it != map.end(); it++)
        n++;

    if (n > 0)
        return true;

    return false;
}

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
    JValue emptyObject = parseJSON("{}");
    JValue simpleObject = parseJSON("{ \"test\": true }");

    if (testEmptyObject(emptyObject))
        return 1;
    if (testSimpleObject(simpleObject))
        return 1;

    return 0;
}
