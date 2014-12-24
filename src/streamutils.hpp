#ifndef _STREAM_UTILS_HPP_
#define _STREAM_UTILS_HPP_

//////////////
// Includes //
#include "parsestream.hpp"

//////////
// Code //

// Checking if a given character has whitespace in it.
bool isWhitespace(char);

// Consuming all of the whitespace in a ParseStream until it reaches a
// non-whitespace character.
int consumeWhitespace(ParseStream&);

#endif
