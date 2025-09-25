#include <iostream>
#include "greeting_utils.h"
#include <string>

using std::cout,std::endl,std::string;

namespace Greeting_Utils{

string create_message(const string& name){
	return "Hello, " + name + "!";
}

char* format_as_c_string(const string& msg){
	int length = msg.size();
	char* arr = new char[length + 1];
	for(int i = 0; i < length; i++){
		arr[i] = msg[i];
	}
	arr[length] = '\0';
	return arr;

}

}

