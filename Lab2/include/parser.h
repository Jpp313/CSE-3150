#ifndef PARSER_H
#define PARSER_H
#include <string>

namespace String_Utils {
    void parseName(const std::string& fullName, std::string* firstName, std::string* lastName);
    std::string get_username(const std::string* email);
}

#endif