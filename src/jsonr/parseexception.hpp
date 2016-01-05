#ifndef _PARSEEXCEPTION_HPP_
#define _PARSEEXCEPTION_HPP_

//////////////
// Includes //
#include <exception>
#include <string>

//////////
// Code //

namespace jsonr {
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
}

#endif
