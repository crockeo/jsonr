#ifndef _JSON_HPP_
#define _JSON_HPP_

//////////////
// Includes //
#include <string>
#include <vector>
#include <map>

//////////
// Code //

namespace jsonr {
    class JValue;

    // A type to represent a piece of JSON.
    enum JType {
        JOBJECT,
        JARRAY,
        JNUMBER,
        JSTRING,
        JBOOL,
        JNULL
    };

    // Declaring each of the types.
    typedef std::map<std::string, JValue> JObject;
    typedef std::vector<JValue>           JArray;
    typedef double                        JNumber;
    typedef std::string                   JString;
    typedef bool                          JBool;

    // A generic JSON value that can represent any type of JSON.
    class JValue {
    private:
        JType type;
        JObject jObject_value;
        JArray jArray_value;
        JNumber jNumber_value;
        JString jString_value;
        JBool jBool_value;

    public:
        // Constructing a JValue as a couple of different types.
        JValue(JObject);
        JValue(JArray);
        JValue(JNumber);
        JValue(JString);
        JValue(JBool);

        // Constructing a JValue as null.
        JValue();

        // Getting the type of the JValue.
        JType getType() const;

        // Checking specifically if this JValue represents something else.
        bool isObject() const;
        bool isArray() const;
        bool isNumber() const;
        bool isString() const;
        bool isBool() const;
        bool isNull() const;

        // Getting the specific values of this JValue.
        JObject jObject() const;
        JArray jArray() const;
        JNumber jNumber() const;
        JString jString() const;
        JBool jBool() const;
    };
}

#endif
