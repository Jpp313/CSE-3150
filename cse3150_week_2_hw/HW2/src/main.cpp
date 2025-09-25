
#include "greeting_utils.h"
#include <iostream>
#include <string>

using std::cout,std::cin,std::string, std::endl;

int main(){
	//cout << "Enter name: "; test.py file does not want input to have Enter Name
	string name;
	std::getline(cin, name);
	string greeting = Greeting_Utils::create_message(name);
	char* c_greeting = Greeting_Utils::format_as_c_string(greeting); 
	cout << c_greeting << endl;
	delete[] c_greeting;
	return 0;
}

