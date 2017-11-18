/*
 * log.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: nullifiedcat
 */

#include "log.hpp"

#include "tools.hpp"

#include <fstream>

namespace log
{

level min_level { level::DEBUG };
bool file_log_enabled { false };
std::ofstream file;

void setup(level lvl, bool write_to_file, std::string filename)
{
    if (write_to_file)
    {
        tools::string_replace(filename, "%USER%", "");
        file = std::ofstream(filename, std::ios::out);
    }
}

void log(level lvl, const char *string)
{

}

void debug(const char *format, ...)
{

}

void info(const char *format, ...)
{

}

void warning(const char *format, ...)
{

}

void error(const char *format, ...)
{

}

}


