#include "load.hpp"

//////////////
// Includes //
#include <fstream>
#include <string>

#include "parser.hpp"
#include "json.hpp"

//////////
// Code //

namespace jsonr {
    // Loading a JSON file from a given path.
    JValue loadJSON(std::string path) throw(std::runtime_error) {
        std::ifstream in(path);
        if (!in.good())
            throw std::runtime_error("Could not open file for JSON parsing: " + path);

        return parseJSON(in);
    }
}
