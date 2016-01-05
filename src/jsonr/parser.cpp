#include "parser.hpp"

//////////////
// Includes //
#include <istream>
#include <string>
#include <vector>
#include <tuple>
#include <map>

#include "parsestream.hpp"
#include "streamutils.hpp"
#include "json.hpp"

//////////
// Code //

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

// Definitions for the functions.
JValue parseJSONObject( ParseStream&) throw (ParseException);
JValue parseJSONArray ( ParseStream&) throw (ParseException);
JValue parseJSONNumber( ParseStream&) throw (ParseException);
JValue parseJSONString( ParseStream&) throw (ParseException);
JValue parseJSONBool  ( ParseStream&) throw (ParseException);
JValue parseJSONNull  ( ParseStream&) throw (ParseException);

// Trying to specifically parse out a JSON object.
JValue parseJSONObject(ParseStream& ps) throw(ParseException) {
    consumeWhitespace(ps);

    if (ps.consume() == '{') {
        std::map<std::string, JValue> valueMap;
        bool first = true;

        while (true) {
            consumeWhitespace(ps);
            if (first && ps.peek() == '}')
                break;

            std::string key = parseJSONString(ps).jString();
            consumeWhitespace(ps);

            if (ps.consume() != ':')
                throw ParseException("In parseJSONObject, expected a ':'.\n");

            consumeWhitespace(ps);
            JValue val = parseJSON(ps);
            valueMap.insert(std::pair<std::string, JValue>(key, val));
            consumeWhitespace(ps);

            char c = ps.consume();
            if (c == '}')
                break;
            else if (c != ',')
                throw ParseException("In parseJSONObject, expected a ','.\n");
        }

        return JValue(valueMap);
    }

    throw ParseException("", false);
}

// Trying to specifically parse out a JSON array.
JValue parseJSONArray(ParseStream& ps) throw(ParseException) {
    consumeWhitespace(ps);

    if (ps.consume() == '[') {
        std::vector<JValue> values;
        bool first = true;

        while (true) {
            consumeWhitespace(ps);
            if (first && ps.peek() == ']')
                break;

            values.push_back(parseJSON(ps));
            consumeWhitespace(ps);

            char c = ps.consume();
            if (c == ']')
                break;
            else if (c != ',')
                throw ParseException("In parseJSONArray, expected a ','.\n");
            first = false;
        }

        return JValue(values);
    }

    throw ParseException("", false);
}

// Trying to specifically parse out a JSON number.
JValue parseJSONNumber(ParseStream& ps) throw(ParseException) {
    consumeWhitespace(ps);

    std::string str;
    bool first = true;
    while (!ps.eof() && !isDelimiter(ps.peek())) {
        char c = ps.consume();

        if (first && c == '-') {
            str.push_back(c);
            first = false;
        } else if (('0' <= c && c <= '9') || c == '.')
            str.push_back(c);
        else {
            if (str.size() == 0)
                throw ParseException("parseJSONNumber", false);
            else
                throw ParseException("In parseJSONNumber, unexpected characters.\n");
        }
    }

    return JValue(stod(str));
}

// Trying to specifically parse out a JSON string.
JValue parseJSONString(ParseStream& ps) throw(ParseException) {
    consumeWhitespace(ps);
    if (ps.peek() == '"') {
        ps.consume();

        std::string str;
        while (ps.peek() != '"') {
            char c = ps.consume();
            if (c == '\n')
                throw ParseException("In parseJSONString, unexpected character '\\n'.\n");

            if (c == '\\') {
                char c2 = ps.consume();

                switch (c2) {
                case '"':
                    str.push_back('"');
                    break;
                case '\\':
                    str.push_back('\\');
                    break;
                case '/':
                    str.push_back('/');
                case 'b':
                    str.push_back('\b');
                    break;
                case 'f':
                    str.push_back('\f');
                    break;
                case 't':
                    str.push_back('\t');
                    break;
                case 'r':
                    str.push_back('\r');
                    break;
                case 'n':
                    str.push_back('\n');
                    break;
                default:
                    throw ParseException("In parseJSONString, unexpected character escape.\n");
                    break;
                }
            } else
                str.push_back(c);
        }

        ps.consume();
        return JValue(str);
    }

    throw ParseException("", false);
}

// Trying to specifically parse out a JSON boolean.
JValue parseJSONBool(ParseStream& ps) throw(ParseException) {
    consumeWhitespace(ps);
    std::string str;

    while (!ps.eof() && !isDelimiter(ps.peek()))
        str.push_back(ps.consume());

    if (str.compare("true") == 0)
        return JValue(true);
    else if (str.compare("false") == 0)
        return JValue(false);

    throw ParseException("", false);
}

// Trying to specifically parse out the null JSON value.
JValue parseJSONNull(ParseStream& ps) throw(ParseException) {
    consumeWhitespace(ps);
    std::string str;

    while (!ps.eof() && !isDelimiter(ps.peek()))
        str.push_back(ps.consume());

    if (str.compare("null") == 0)
        return JValue();

    throw ParseException("", false);
}

// Attempting to perform a parse - and then backing up on an error.
JValue attemptParse(ParseStream& ps, JValue (*parseFn)(ParseStream&)) throw(ParseException) {
    int sl = ps.getLoc();
    try { return parseFn(ps); }
    catch (const ParseException& e) {
        ps.back(ps.getLoc() - sl);
        throw e;
    }
}

// Parsing out a block of JSON from a ParseStream.
JValue parseJSON(ParseStream ps) throw(ParseException) {
    if (ps.eof())
        throw ParseException("Empty parse stream.");

    std::vector<JValue (*)(ParseStream&)> fns {
        &parseJSONObject,
        &parseJSONArray,
        &parseJSONNumber,
        &parseJSONString,
        &parseJSONBool,
        &parseJSONNull   
    };

    for (auto it = fns.begin(); it != fns.end(); it++) {
        try { return attemptParse(ps, *it); }
        catch (const ParseException& e) {
            if (e.didMatch())
                throw e;
        }
    }

    throw ParseException("In parseJSON, failed to match.\n");
}

// Parsing out a block of JSON from a string.
JValue parseJSON(const std::string str) throw(ParseException) {
    ParseStream ps(str);
    return parseJSON(ps);
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
