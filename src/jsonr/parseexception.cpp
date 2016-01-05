#include "parseexception.hpp"

//////////
// Code //

namespace jsonr {
    // Creating a parse exception.
    ParseException::ParseException(std::string type) {
        this->type = type;
        this->matched = true;
    }

    // Creating a failed-to-match parse exception.
    ParseException::ParseException(std::string type, bool matched) {
        this->type = type;
        this->matched = matched;
    }

    // Returning a string to refer to this exception.
    const char* ParseException::what() const throw() { return this->type.c_str(); }

    // Returns if the ParseException matched.
    bool ParseException::didMatch() const {
        return this->matched;
    }
}
