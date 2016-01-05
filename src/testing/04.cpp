#include "04.hpp"

//////////////
// Includes //
#include "../jsonr/parser.hpp"
#include "../jsonr/json.hpp"

//////////
// Code //

using namespace jsonr;

// Attempting to test parseJSON for 'null' values.
int runTest04() {
    JValue jNull;

    try { jNull = parseJSON("null"); }
    catch (const ParseException& e) { return 1; }
    
    if (!jNull.isNull())
        return 1;

    return 0;
}

