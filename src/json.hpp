#ifndef _JSON_HPP_
#define _JSON_HPP_

//////////
// Code //

// A type to represent a piece of JSON.
enum JType {
    JOBJECT,
    JARRAY,
    JNUMBER,
    JSTRING,
    JBOOL
};

// Declaring each of the types.
typedef std::vector<std::string, JValue> JObject;
typedef std::vector<JValue>              JArray;
typedef double                           JNumber;
typedef std::string                      JString;
typedef bool                             JBool;

#endif
