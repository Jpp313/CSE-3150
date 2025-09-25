#ifndef GREETING_UTILS_H
#define GREETING_UTILS_H
#include <string>

namespace Greeting_Utils{
	std::string create_message(const std::string& name);
	char* format_as_c_string(const std::string& msg);
}

#endif
