#ifndef _PARSER_HPP_
#define _PARSER_HPP_

//////////////
// Includes //
#include <exception>
#include <istream>
#include <string>

#include "parsestream.hpp"
#include "json.hpp"

//////////
// Code //

// An exception to represent a function failing to parse.
class ParseException : public std::exception {
public:
    // Creating a parse exception.
    ParseException(std::string);

    // Creating a failed-to-match parse exception.
    ParseException(std::string, bool);

    // Returning a string to refer to this exception.
    const char* what() const throw();

    // Returns if the ParseException matched.
    bool didMatch() const;

private:
    std::string type;
    bool matched;
};

// Parsing out a block of JSON from a ParseStream.
JValue parseJSON(ParseStream) throw(ParseException);

// Parsing out a block of JSON from a string.
JValue parseJSON(const std::string) throw(ParseException);

// Parsing out a block of JSON from an istream.
JValue parseJSON(std::istream&) throw(ParseException);

#endif