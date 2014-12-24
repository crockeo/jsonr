#include "04.hpp"

//////////////
// Includes //
#include "../parser.hpp"
#include "../json.hpp"

//////////
// Code //

// Attempting to test parseJSON for 'null' values.
int runTest04() {
    JValue jNull;

    try { jNull = parseJSON("null"); }
    catch (const ParseException& e) { return 1; }
    
    if (!jNull.isNull())
        return 1;

    return 0;
}

