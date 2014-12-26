#include "05.hpp"

//////////////
// Includes //
#include <fstream>

#include "../parser.hpp"
#include "../json.hpp"

//////////
// Code //

// Testing the empty object.
bool testEmptyObject(const JValue& emptyObject) {
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
bool testSimpleObject(const JValue& simpleObject) {
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

#include <iostream>

// Testing the complex object.
bool testComplexObject(const JValue& complexObject) {
    if (!complexObject.isObject())
        return true;

    auto map = complexObject.jObject();

    // Testing "_id".
    if (!map["_id"].isString() || map["_id"].jString().compare("549d99dee80226183c018588") != 0)
        return true;

    // Testing "index".
    if (!map["index"].isNumber() || (int)map["index"].jNumber() != 0)
        return true;

    // Testing "guid"
    if (!map["guid"].isString() || map["guid"].jString().compare("1db598d0-3333-4aea-aa5e-4be986236e56") != 0)
        return true;

    // Testing "isActive"
    if (!map["isActive"].isBool() || map["isActive"].jBool() != false)
        return true;

    // Testing "balance"
    if (!map["balance"].isString() || map["balance"].jString().compare("$2,983.05") != 0)
        return true;

    // Testing "picture"
    if (!map["picture"].isString() || map["picture"].jString().compare("http://placehold.it/32x32") != 0)
        return true;

    // Testing "age"
    if (!map["age"].isNumber() || (int)map["age"].jNumber() != 34)
        return true;

    // Testing "eyeColor"
    if (!map["eyeColor"].isString() || map["eyeColor"].jString().compare("brown") != 0)
        return true;

    // Testing "name"
    if (!map["name"].isString() || map["name"].jString().compare("Hale Bridges") != 0)
        return true;

    // Testing "gender"
    if (!map["gender"].isString() || map["gender"].jString().compare("male") != 0)
        return true;

    // Testing "company"
    if (!map["company"].isString() || map["company"].jString().compare("ENTROPIX") != 0)
        return true;

    // Testing "email"
    if (!map["email"].isString() || map["email"].jString().compare("halebridges@entropix.com") != 0)
        return true;

    // Testing "phone"
    if (!map["phone"].isString() || map["phone"].jString().compare("+1 (879) 419-2839") != 0)
        return true;

    // Testing "address"
    if (!map["address"].isString() || map["address"].jString().compare("256 Chester Court, Bergoo, Massachusetts, 3694") != 0)
        return true;

    // Testing "about"
    if (!map["about"].isString() || map["about"].jString().compare("Fugiat cupidatat adipisicing sit laborum reprehenderit occaecat laboris eiusmod et. Cupidatat dolore occaecat eu voluptate laborum non esse et labore laboris elit dolor adipisicing. Dolore ex eu et id Lorem. Irure ullamco enim nisi et excepteur ad elit ut sint magna magna magna dolore. Amet nisi et aliqua adipisicing duis et proident do. Velit sit elit tempor eu. Eu anim aliquip laboris nisi aliqua irure proident do.\r\n") != 0)
        return true;

    // Testing "registered"
    if (!map["registered"].isString() || map["registered"].jString().compare("2014-12-23T05:02:09 +05:00") != 0)
        return true;

    // Testing "latitude"
    if (!map["latitude"].isNumber() || map["latitude"].jNumber() != 78.328387)
        return true;

    // Testing "longitude"
    if (!map["longitude"].isNumber() || map["longitude"].jNumber() != -81.043504)
        return true;

    // Testing "tags"
    if (map["tags"].isArray()) {
        auto tags = map["tags"].jArray();

        for (auto it = tags.begin(); it != tags.end(); it++)
            std::cout << it->jString() << " ";
        std::cout << std::endl;

        if (!tags[0].isString() || tags[0].jString().compare("voluptate") != 0)
            return true;
        if (!tags[1].isString() || tags[1].jString().compare("incididunt") != 0)
            return true;
        if (!tags[2].isString() || tags[2].jString().compare("consectetur") != 0)
            return true;
        if (!tags[3].isString() || tags[3].jString().compare("consectetur") != 0)
            return true;
        if (!tags[4].isString() || tags[4].jString().compare("voluptate") != 0)
            return true;
        if (!tags[5].isString() || tags[5].jString().compare("dolore") != 0)
            return true;
        if (!tags[6].isString() || tags[6].jString().compare("in") != 0)
            return true;
    } else
        return true;

    if (map["friends"].isArray()) {
        auto friends = map["friends"].jArray();
        for (auto it = friends.begin(); it != friends.end(); it++)
            if (!it->isObject())
                return true;

        for (int i = 0; i < friends.size(); i++) {
            if (!friends[i].isObject())
                return true;

            auto smap = friends[i].jObject();
            std::string name;

            switch (i) {
            case 0:
                name = "Connie Douglas";
                break;
            case 1:
                name = "Charlotte Collins";
                break;
            case 2:
                name = "Esperanza Emerson";
                break;
            }

            if (!smap["id"].isNumber() || (int)smap["id"].jNumber() != i)
                return true;
            if (!smap["name"].isString() || smap["name"].jString().compare(name) != 0)
                return true;
        }
    } else
        return true;

    if (!map["greeting"].isString() || map["greeting"].jString().compare("Hello, Hale Bridges! You have 6 unread messages.") != 0)
        return true;

    if (!map["favoriteFruit"].isString() || map["favoriteFruit"].jString().compare("strawberry") != 0)
        return true;

    return false;
}

// Attempting to test parseJSON for 'null' values.
int runTest05() {
    JValue emptyObject = parseJSON("{ }");
    JValue simpleObject = parseJSON("{ \"test\": true }");

    // Loading a piece of test JSON from a file.
    std::ifstream reader("data/complex.json");
    if (!reader.good())
        return 2;
    JValue complexObject = parseJSON(reader);
    reader.close();

    if (testEmptyObject(emptyObject))
        return 1;
    if (testSimpleObject(simpleObject))
        return 1;
    if (testComplexObject(complexObject))
        return 1;

    return 0;
}
