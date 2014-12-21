#ifndef _PARSER_HPP_
#define _PARSER_HPP_

//////////////
// Includes //
#include <istream>
#include <string>

#include "json.hpp"

//////////
// Code //

// Parsing out a block of JSON from a string.
JValue parseJSON(const std::string&);

// Parsing out a block of JSON from an istream.
JValue parseJSON(std::istream&);

#endif
