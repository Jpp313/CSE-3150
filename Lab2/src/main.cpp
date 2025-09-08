#include "parser.h"
#include <iostream>
#include <string>

using std::cout,std::cin,std::endl,std::string, std::cerr;

int main(){
    cerr << "Enter Full Name: ";
    string full_name;
    getline(cin, full_name);
    cerr << "Enter email: ";
    string email;
    getline(cin, email);
    int size = 1;
    string* first_name = new string[size];
    string* last_name = new string[size];
    String_Utils::parseName(full_name,first_name,last_name);
    cout << "First Name: " << first_name[0] << endl;
    cout << "Last Name: " << last_name[0] << endl;
    cout << "Username: " << String_Utils::get_username(&email) << endl;
    delete[] first_name;
    delete[] last_name;
    return 0;
}