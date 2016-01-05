#include "03.hpp"

//////////////
// Includes //
#include <vector>

#include "../jsonr/parser.hpp"
#include "../jsonr/json.hpp"
#include "utils.hpp"

//////////
// Code //

// Testing the empty array.
bool testEmptArray(const JValue& emptArray) {
    return !(emptArray.isArray() && emptArray.jArray().size() == 0);
}

// Testing the number array.
bool testNumArray(const JValue& numArray) {
    if (!numArray.isArray())
        return true;
    std::vector<JValue> vals = numArray.jArray();

    for (int i = 0; i < vals.size(); i++)
        if (!vals[i].isNumber() || !around((double)(i + 1), vals[i].jNumber(), 1))
            return true;

    return false;
}

// Testing the string array.
bool testStrArray(const JValue& strArray) {
    if (!strArray.isArray())
        return true;

    auto validate = [](const JValue& str, const std::string& tStr) -> bool const {
        if (!str.isString() || str.jString().compare(tStr) != 0)
            return true;
        return false;
    };

    std::vector<std::string> targets;
    targets.push_back("testing");
    targets.push_back("with spaces");
    targets.push_back("and a 'quote with spaces after!!!");

    for (int i = 0; i < targets.size(); i++) {
        JValue v = strArray.jArray()[i];
        if (validate(v, targets[i])) {
            std::string out;
            if (v.isNull())
                out = "null";
            else
                out = v.jString();

            return true;
        }
    }

    return false;
}

// Testing the bool array.
bool testBoolArray(const JValue& boolArray) {
    return false;
}

// Testing the Array portion of parseJSON.
int runTest03() {
    JValue emptArray = parseJSON("[]");
    JValue numArray  = parseJSON("[1, 2, 3, 4, 5]");
    JValue strArray  = parseJSON("[\"testing\", \"with spaces\", \"and a 'quote with spaces after!!!\"]");
    JValue boolArray = parseJSON("[true, false, true]");

    if (testEmptArray(emptArray))
        return 1;
    if (testNumArray(numArray))
        return 1;
    if (testStrArray(strArray))
        return 1;
    if (testBoolArray(boolArray))
        return 1;

    return 0;
}
