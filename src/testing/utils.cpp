#include "utils.hpp"

//////////
// Code //

// Checking if a value is around the target.
bool around(double target, double num, double range) {
    return num >= target - range &&
           num <= target + range;
}
