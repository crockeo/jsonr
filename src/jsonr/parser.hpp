#ifndef _PARSER_HPP_
#define _PARSER_HPP_

//////////////
// Includes //
#include <istream>
#include <string>

#include "parseexception.hpp"
#include "parsestream.hpp"
#include "json.hpp"

//////////
// Code //

// Parsing out a block of JSON from a ParseStream.
JValue parseJSON(ParseStream&) throw(ParseException);

// Parsing out a block of JSON from a string.
JValue parseJSON(const std::string) throw(ParseException);

// Parsing out a block of JSON from an istream.
JValue parseJSON(std::istream&) throw(ParseException);

#endif
