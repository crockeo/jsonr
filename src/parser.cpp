#include "parser.hpp"

//////////////
// Includes //
#include <istream>
#include <string>
#include <vector>
#include <tuple>

#include "parsestream.hpp"
#include "streamutils.hpp"
#include "json.hpp"

//////////
// Code //

// Creating a parse exception.
ParseException::ParseException(std::string type) {
    this->type = type;
}

// Returning a string to refer to this exception.
const char* ParseException::what() const throw() {
    return ("Failed to parse a " + this->type + " piece of JSON.").c_str();
}

//// Trying to specifically parse out a JSON object.
//JValue parseJSONObject(ParseStream& ps) throw(ParseException) {
    //throw ParseException("JObject");
//}

//// Trying to specifically parse out a JSON array.
//JValue parseJSONArray(ParseStream& ps) throw(ParseException) {
    //if (str[0] == '[' && str[str.size() - 1] == ']') {
        //std::string useStr = str.substr(1, str.size() - 2);
        //if (useStr.compare("") == 0)
            //return JValue();

        //std::vector<JValue> jValues;
        //std::tuple<std::string, std::string> tup;
        //for (tup = untilChar(useStr, ','); std::get<0>(tup).compare("") != 0; tup = untilChar(std::get<1>(tup), ','))
            //jValues.push_back(parseJSON(stripWhitespace(std::get<0>(tup))));

        //return JValue(jValues);
    //}

    //throw ParseException("parseJSONArray");
//}

// Trying to specifically parse out a JSON number.
JValue parseJSONNumber(ParseStream& ps) throw(ParseException) {
    consumeWhitespace(ps);

    std::string str;
    bool first = true;
    while (!ps.eof() && !isWhitespace(ps.peek())) {
        char c = ps.consume();

        if (first && c == '-') {
            str.push_back(c);
            first = false;
        } else if (('0' <= c && c <= '9') || c == '.')
            str.push_back(c);
        else
            throw ParseException("parseJSONNumber");
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
                throw ParseException("parseJSONString");

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
                    throw ParseException("parseJSONString");
                    break;
                }
            } else
                str.push_back(c);
        }

        return JValue(str);
    }

    throw ParseException("parseJSONString");
}

// Trying to specifically parse out a JSON boolean.
JValue parseJSONBool(ParseStream& ps) throw(ParseException) {
    consumeWhitespace(ps);
    std::string str;

    while (!ps.eof() && !isWhitespace(ps.peek()))
        str.push_back(ps.consume());

    if (str.compare("true") == 0)
        return JValue(true);
    else if (str.compare("false") == 0)
        return JValue(false);

    throw ParseException("JSONBool");
}

// Trying to specifically parse out the null JSON value.
JValue parseJSONNull(ParseStream& ps) throw(ParseException) {
    consumeWhitespace(ps);
    std::string str;

    while (!ps.eof() && !isWhitespace(ps.peek()))
        str.push_back(ps.consume());

    if (str.compare("null") == 0)
        return JValue();
    throw ParseException("parseJSONNull");
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
JValue parseJSON(ParseStream& ps) throw(ParseException) {
    std::vector<JValue (*)(ParseStream&)> fns;
    fns.push_back(&parseJSONNumber);
    fns.push_back(&parseJSONString);
    fns.push_back(&parseJSONBool);
    fns.push_back(&parseJSONNull);

    for (auto it = fns.begin(); it != fns.end(); it++) {
        try { return attemptParse(ps, *it); }
        catch (const ParseException& e) { }
    }

    throw ParseException("parseJSON");
}

// Parsing out a block of JSON from a string.
JValue parseJSON(const std::string& str) throw(ParseException) {
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
