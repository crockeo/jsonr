#ifndef _LOAD_HPP_
#define _LOAD_HPP_

//////////////
// Includes //
#include <exception>
#include <string>

#include "json.hpp"

//////////
// Code //

namespace jsonr {
    // Loading a JSON file from a given path.
    JValue loadJSON(std::string) throw(std::runtime_error);
}

#endif
