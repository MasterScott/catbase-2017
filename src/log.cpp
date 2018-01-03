/*
 * log.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: nullifiedcat
 */

/*
 * This file is a monstrous mix of C and C++
 */

#include "log.hpp"

#include "tools.hpp"

#include <time.h>
#include <stdarg.h>
#include <fstream>

namespace log
{

std::ofstream file;

void setup(std::string filename)
{
    tools::string_replace(filename, "%USER%", tools::get_user_name());
    file = std::ofstream(filename, std::ios::out);
}

static const char *level_names[] = { "NONE", "ERROR", "WARNING", "INFO", "DEBUG", "SILLY" };

void log_internal(catbase_log_level lvl, const char *format, ...)
{
    char buffer[1024];
    struct tm *time_info = nullptr;
    time_t current_time;
    char time_string[10];
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_string, sizeof(time_string), "%H:%M:%S", time_info);
    int written = sprintf(buffer, "[%-7s] [%s] ",
                          level_names[static_cast<int>(lvl)], time_string);

    va_list list;
    va_start(list, format);
    vsnprintf(buffer + 21, 1002, format, list);
    va_end(list);

    if (file.good())
    {
        // Write and flush
        file << buffer << std::endl;
    }
}

}
