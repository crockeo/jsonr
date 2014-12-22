#include "parser.hpp"

//////////////
// Includes //
#include <istream>
#include <string>
#include <vector>

#include "json.hpp"

//////////
// Code //

// Checking if a given string is whitespace.
bool isWhitespace(char c) {
    switch (c) {
    case ' ':
    case '\t':
    case '\r':
    case '\n':
        return true;
    default:
        break;
    }

    return false;
}

// Stripping the whitespace out of a string.
std::string stripWhitespace(const std::string& str) {
    std::string ret;

    for (auto it = str.begin(); it != str.end(); it++)
        if (!isWhitespace(*it))
            ret.push_back(*it);

    return ret;
}

// Trying to specifically parse out a JSON object.
JValue parseJSONObject(const std::string& str) {
    return JValue();
}

// Trying to specifically parse out a JSON array.
JValue parseJSONArray(const std::string& str) {
    return JValue();
}

// Trying to specifically parse out a JSON number.
JValue parseJSONNumber(const std::string& str) {
    return JValue();
}

// Trying to specifically parse out a JSON string.
JValue parseJSONString(const std::string& str) {
    return JValue();
}

// Trying to specifically parse out a JSON boolean.
JValue parseJSONBool(const std::string& str) {
    return JValue();
}

// Parsing out a block of JSON from a string.
JValue parseJSON(const std::string& str) {
    std::vector<JValue (*)(const std::string&)> fns;
    fns.push_back(&parseJSONObject);
    fns.push_back(&parseJSONArray);
    fns.push_back(&parseJSONNumber);
    fns.push_back(&parseJSONString);
    fns.push_back(&parseJSONBool);

    JValue val;
    for (auto it = fns.begin(); it != fns.end(); it++) {
        val = (*it)(str);
        if (!val.isNull())
            return val;
    }

    return JValue();
}

// Parsing out a block of JSON from an istream.
JValue parseJSON(std::istream& stream) {
    std::string line, all;

    while (!stream.eof()) {
        std::getline(stream, line);
        all += line;
    }

    return parseJSON(all);
}
