#include "load.hpp"

//////////////
// Includes //
#include <fstream>
#include <string>

#include "parser.hpp"
#include "json.hpp"

//////////
// Code //

// Loading a JSON file from a given path.
JValue loadJSON(std::string path) {
    std::ifstream in(path);
    if (!in.good())
        return JValue();

    return parseJSON(in);
}
