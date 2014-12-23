#include "parser.hpp"

//////////////
// Includes //
#include <istream>
#include <string>
#include <vector>
#include <tuple>

#include "json.hpp"

//////////
// Code //

// Creating a parse exception.
ParseException::ParseException() {}

// Returning a string to refer to this exception.
const char* ParseException::what() const throw() {
    return "Failed to parse a piece of JSON.";
}

// Checking if a given string is whitespace.
bool isWhitespace(char c) {
    switch (c) {
    case ' ':
    case '\t':
    case '\r':
    case '\n':
        return true;
    default:
        break;
    }

    return false;
}

// Returns the strings before and after a delimiter character.
std::tuple<std::string, std::string> untilChar(const std::string& str, char delim) {
    int n;
    for (n = 0; n < str.size(); n++)
        if (str[n] == delim)
            break;

    if (n + 1 >= str.size())
        return std::make_tuple(str, "");
    return std::make_tuple(str.substr(0, n), str.substr(n + 1, str.size() - 1));
}

// Checking if a character is a quote.
bool isQuote(char c) {
    return c == '"' || c == '\'';
}

// Stripping the whitespace out of a string.
std::string stripWhitespace(const std::string& str) {
    std::string ret;

    for (auto it = str.begin(); it != str.end(); it++)
        if (!isWhitespace(*it))
            ret.push_back(*it);

    return ret;
}

// Trying to specifically parse out a JSON object.
JValue parseJSONObject(const std::string& str) {
    return JValue();
}

// Trying to specifically parse out a JSON array.
JValue parseJSONArray(const std::string& str) {
    if (str[0] == '[' && str[str.size() - 1] == ']') {
        std::string useStr = str.substr(1, str.size() - 2);
        if (useStr.compare("") == 0)
            return JValue();

        std::vector<JValue> jValues;
        std::tuple<std::string, std::string> tup;
        for (tup = untilChar(useStr, ','); std::get<0>(tup).compare("") != 0; tup = untilChar(std::get<1>(tup), ','))
            jValues.push_back(parseJSON(stripWhitespace(std::get<0>(tup))));

        return JValue(jValues);
    }

    return JValue();
}

// Trying to specifically parse out a JSON number.
JValue parseJSONNumber(const std::string& str) {
    try {
        return JValue(stod(str));
    } catch (const std::invalid_argument& ia) {
        return JValue();
    }
}

// Trying to specifically parse out a JSON string.
JValue parseJSONString(const std::string& str) {
    if (isQuote(*str.begin()) && isQuote(*(str.end() - 1))) {
        char fq = *str.begin();
        bool ok = false;
        std::string accum;

        for (auto it = str.begin() + 1; it != str.end() - 1; it++) {
            if (!ok && *it == fq)
                return JValue();
            else if ((*it) == '\\')
                ok = true;
            else
                ok = false;

            accum.push_back(*it);
        }

        return JValue(accum);
    }

    return JValue();
}

// Trying to specifically parse out a JSON boolean.
JValue parseJSONBool(const std::string& str) {
    if (str.compare("true") == 0)
        return JValue(true);
    else if (str.compare("false") == 0)
        return JValue(false);
    else
        return JValue();
}

// Trying to specifically parse out the null JSON value.
JValue parseJSONNull(const std::string& str) {
    if (str.compare("null") == 0)
        return JValue();
    return JValue();
}

// Parsing out a block of JSON from a string.
JValue parseJSON(const std::string& str) throw (ParseException) {
    std::vector<JValue (*)(const std::string&)> fns;
    fns.push_back(&parseJSONObject);
    fns.push_back(&parseJSONArray);
    fns.push_back(&parseJSONNumber);
    fns.push_back(&parseJSONString);
    fns.push_back(&parseJSONBool);
    fns.push_back(&parseJSONNull);

    JValue val;
    for (auto it = fns.begin(); it != fns.end(); it++) {
        val = (*it)(str);
        if (!val.isNull())
            return val;
    }

    throw ParseException();
    return JValue();
}

// Parsing out a block of JSON from an istream.
JValue parseJSON(std::istream& stream) throw(ParseException) {
    std::string line, all;

    while (!stream.eof()) {
        std::getline(stream, line);
        all += line;
    }

    return parseJSON(all);
}
