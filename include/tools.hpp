/*
 * tools.hpp
 *
 *  Created on: Nov 18, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include <string>

namespace tools
{

void string_replace(std::string& string, std::string what, std::string with_what);

const std::string& get_user_name();

}



