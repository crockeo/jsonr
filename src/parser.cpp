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

//// Checking if a given string is whitespace.
//bool isWhitespace(char c) {
    //switch (c) {
    //case ' ':
    //case '\t':
    //case '\r':
    //case '\n':
        //return true;
    //default:
        //break;
    //}

    //return false;
//}

//// Returns the strings before and after a delimiter character.
//std::tuple<std::string, std::string> untilChar(ParseStream& ps, char delim) {
    //int n;
    //for (n = 0; n < str.size(); n++)
        //if (str[n] == delim)
            //break;

    //if (n + 1 >= str.size())
        //return std::make_tuple(str, "");
    //return std::make_tuple(str.substr(0, n), str.substr(n + 1, str.size() - 1));
//}

//// Checking if a character is a quote.
//bool isQuote(char c) {
    //return c == '"' || c == '\'';
//}

//// Stripping the whitespace out of a string. Unless it's within a pair of quote
//// characters. Then it doesn't. :)
//std::string stripWhitespace(ParseStream& ps) {
    //std::string ret;

    //bool mode = true;
    //char quoteChar = '\0';

    //for (auto it = str.begin(); it != str.end(); it++) {
        //if (isQuote(*it) && (quoteChar == '\0' || *it == quoteChar)) {
            //mode = !mode;
            //quoteChar = *it;
        //}

        //if (!mode)
            //ret.push_back(*it);
        //else if (mode && !isWhitespace(*it))
            //ret.push_back(*it);
    //}

    //return ret;
//}

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

//// Trying to specifically parse out a JSON number.
//JValue parseJSONNumber(ParseStream& ps) throw(ParseException) {
    //try {
        //return JValue(stod(str));
    //} catch (const std::invalid_argument& ia) {
        //throw ParseException("parseJSONNumber");
    //}
//}

//// Trying to specifically parse out a JSON string.
//JValue parseJSONString(ParseStream& ps) throw(ParseException) {
    //if (isQuote(*str.begin()) && isQuote(*(str.end() - 1))) {
        //char fq = *str.begin();
        //bool ok = false;
        //std::string accum;

        //for (auto it = str.begin() + 1; it != str.end() - 1; it++) {
            //if (!ok && *it == fq)
                //return JValue();
            //else if ((*it) == '\\')
                //ok = true;
            //else
                //ok = false;

            //accum.push_back(*it);
        //}

        //return JValue(accum);
    //}

    //throw ParseException("parseJSONString");
//}

//// Trying to specifically parse out a JSON boolean.
//JValue parseJSONBool(ParseStream& ps) throw(ParseException) {
    //if (str.compare("true") == 0)
        //return JValue(true);
    //else if (str.compare("false") == 0)
        //return JValue(false);
    //throw ParseException("parseJSONBool");
//}

// Trying to specifically parse out the null JSON value.
JValue parseJSONNull(ParseStream& ps) throw(ParseException) {
    consumeWhitespace(ps);

    std::string str;
    for (int i = 0; i < 4; i++) {
        char c = ps.consume();
        if (c == '\0')
            break;

        str.push_back(c);
    }

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
