/*
 * tools.hpp
 *
 *  Created on: Nov 18, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include <string>
#include <sstream>

namespace tools
{

void string_replace(std::string& string, const std::string& what, const std::string& with_what);

const std::string& get_user_name();

/* Internal functions */
inline void makestring_internal(std::stringstream& stream) {}

template<typename T, typename... Targs>
void makestring_internal(std::stringstream& stream, T value, Targs... args)
{
    stream << value;
    makestring_internal(stream, args...);
}

/* This is the one you want */
template<typename... Args>
std::string makestring(const Args&... args) {
    std::stringstream stream;
    makestring_internal(stream, args...);
    return stream.str();
}

}



