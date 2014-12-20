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
JValue parseJSON(const std::istream& stream) {
    std::string all;
    std::string line;

    // Reading all of the lines.
    while (!stream.eof()) {
        // TODO: Find out why this isn't working.
        // DOCS: http://www.cplusplus.com/reference/string/string/getline/
        std::getline(stream, line);
        all += line;
    }

    return parseJSON(all);
}
