#include "parser.hpp"

//////////////
// Includes //
#include <istream>
#include <string>

#include "json.hpp"

//////////
// Code //

// Parsing out a block of JSON from a string.
JValue parseJSON(std::string str) {
    return JValue();
}

// Parsing out a block of JSON from an istream.
JValue parseJSON(std::istream stream) {
    std::string line, all;

    // Reading all of the lines.
    while (!stream.eof()) {
        std::getline(stream, line);
        all += line;
    }

    return parseJSON(all);
}
