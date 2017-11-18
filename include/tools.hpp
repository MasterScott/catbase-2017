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

void string_replace(std::string& string, const std::string& what, const std::string& with_what);

const std::string& get_user_name();

}



