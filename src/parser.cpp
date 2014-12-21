#include "parser.hpp"

//////////////
// Includes //
#include <istream>
#include <string>

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

// Parsing out a block of JSON from a string.
JValue parseJSON(const std::string& str) {

    return JValue();
}

// Parsing out a block of JSON from an istream.
JValue parseJSON(std::istream& stream) {
    std::string line, all;

    // Reading all of the lines.
    while (!stream.eof()) {
        std::getline(stream, line);
        all += line;
    }

    // TODO: TURN AN IFSTREAM INTO AN ISTREAM.
    //       PLS.

    return parseJSON(all);
}
