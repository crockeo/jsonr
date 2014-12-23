#include "parsestream.hpp"

//////////////
// Includes //
#include <string>

//////////
// Code //

// Constructing a parse stream from a string.
ParseStream::ParseStream(std::string str) : data(str) { }

// Constructing an empty parse strema.
ParseStream::ParseStream() { this->data = ""; }

// Returns true when there are no more characters to consume or peek.
bool ParseStream::eof() const { return this->loc >= this->data.size(); }

// Peeking at a character n in the future. When eof() is set, it returns a
// null character.
char ParseStream::peek(int n) const {
    if (this->loc + n >= this->data.size())
        return '\0';
    return this->data[this->loc + n];
}

// Peeking at the current character. When eof() is set, it returns a null
// character.
char ParseStream::peek() const {
    if (this->eof())
        return '\0';
    return this->data[loc];
}

// Consuming the current character. When eof() is set, it returns a null
// character and does not increment the loc.
char ParseStream::consume() {
    if (this->eof())
        return '\0';
    char c = this->data[loc++];
    return c;
}

// Backing up the stream n times.
void ParseStream::back(int n) {
    this->loc -= n;
    if (this->loc < 0)
        this->loc = 0;
}

// Accessing the whole data string.
std::string ParseStream::getData() const { return this->data; }

// Accessing the location.
int ParseStream::getLoc() const { return this->loc; }
