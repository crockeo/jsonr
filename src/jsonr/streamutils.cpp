#include "streamutils.hpp"

//////////////
// Includes //
#include "parsestream.hpp"

//////////
// Code //

// Checking if a given character has whitespace in it.
bool isWhitespace(char c) {
    switch (c) {
    case ' ':
    case '\t':
    case '\r':
    case '\n':
        return true;
    default:
        return false;
    }
}

// Checking if a given character is a delimiter.
bool isDelimiter(char c) {
    return isWhitespace(c) || c == ',' || c == ']' || c == '}';
}

// Consuming all of the whitespace in a ParseStream until it reaches a
// non-whitespace character.
int consumeWhitespace(ParseStream& ps) {
    int n = 0;

    while (!ps.eof() && isWhitespace(ps.peek())) {
        ps.consume();
        n++;
    }

    return n;
}
