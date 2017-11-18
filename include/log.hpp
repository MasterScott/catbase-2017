/*
 * log.hpp
 *
 *  Created on: Nov 18, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include <string>

namespace log
{

enum class level
{
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

void setup(level lvl, bool write_to_file, std::string filename);

void log(level lvl, const char *string);
void debug(const char *format, ...);
void info(const char *format, ...);
void warning(const char *format, ...);
void error(const char *format, ...);

}
