/*
 * tools.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: nullifiedcat
 */

#include "tools.hpp"

#include <unistd.h>
#include <pwd.h>

namespace tools
{

void string_replace(std::string& string, std::string what, std::string with_what)
{
    size_t index = string.find(what);
    while (index != std::string::npos) {
        string.replace(index, what.size(), with_what);
        index = string.find(what, index + with_what.size());
    }
}

const std::string& get_user_name()
{
    static std::string username = []()
        {
            passwd *pwd = getpwuid(getuid());
            return (pwd && pwd->pw_name) ?
                    std::string(pwd->pw_name) :
                    "null";
        }();
}

}
