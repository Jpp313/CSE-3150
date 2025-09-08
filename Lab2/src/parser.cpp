#include <iostream>
#include "parser.h"
#include <string>

using std::cout,std::cin,std::endl,std::string;

namespace String_Utils {

void parseName(const string& fullName, string* firstName, string* lastName){
    // instead of instantly relying on first space for first name we use last space for the 2nd half
    size_t firstSpace = fullName.find(' ');
    size_t lastSpace = fullName.rfind(' ');
    if (firstSpace != string::npos) {
        *firstName = fullName.substr(0, firstSpace); // first name
    } else {
        *firstName = fullName; 
    }
    if (lastSpace != string::npos) {
        *lastName = fullName.substr(lastSpace + 1); // last name 
    } else {
        *lastName = ""; 
    }
}

string get_username(const string* email) {

    size_t a_pos = (*email).find('@');
    return (*email).substr(0,a_pos);
    
}
}