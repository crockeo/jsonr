#ifndef _PARSE_STREAM_HPP_
#define _PARSE_STREAM_HPP_

//////////////
// Includes //
#include <string>

//////////
// Code //

namespace jsonr {
    // A stream to represent some kind of input.
    class ParseStream {
    private:
        std::string data;
        int loc;

    public:
        // Constructing a parse stream from a string.
        ParseStream(std::string);

        // Constructing an empty parse strema.
        ParseStream();

        // Returns true when there are no more characters to consume or peek.
        bool eof() const;

        // Peeking at a character n in the future. When eof() is set, it returns a
        // null character.
        char peek(int) const;

        // Peeking at the current character. When eof() is set, it returns a null
        // character.
        char peek() const;

        // Consuming the current character. When eof() is set, it returns a null
        // character and does not increment the loc.
        char consume();
        
        // Backing up the stream n times.
        void back(int);

        // Accessing the whole data string.
        std::string getData() const;

        // Accessing the location.
        int getLoc() const;
    };
}

#endif
