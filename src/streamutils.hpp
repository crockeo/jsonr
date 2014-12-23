#ifndef _STREAM_UTILS_HPP_
#define _STREAM_UTILS_HPP_

//////////////
// Includes //
#include "parsestream.hpp"

//////////
// Code //

// Consuming all of the whitespace in a ParseStream until it reaches a
// non-whitespace character.
int consumeWhitespace(ParseStream&);

#endif
