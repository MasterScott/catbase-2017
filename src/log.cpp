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

level min_level { level::DEBUG };
bool file_log_enabled { false };
std::ofstream file;

void setup(level lvl, bool write_to_file, std::string filename)
{
    min_level = lvl;
    file_log_enabled = write_to_file;
    if (write_to_file)
    {
        tools::string_replace(filename, "%USER%", tools::get_user_name());
        file = std::ofstream(filename, std::ios::out);
    }
}

static const char *level_names[] =
        {
                "DEBUG", "INFO", "WARNING", "ERROR"
        };

static void log_internal(level lvl, const char *format, const va_list list)
{
    char buffer[1024];
    struct tm *time_info = nullptr;
    time_t current_time;
    char time_string[10];
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_string, sizeof(time_string), "%H:%M:%S", time_info);
    int written = sprintf(buffer, "[%-7s] [%s] ", level_names[static_cast<int>(lvl)], time_string);
    vsnprintf(buffer + 21, 1002, format, list);

    if (file_log_enabled && file.good())
    {
        // Write and flush
        file << buffer << std::endl;
    }
}

void debug(const char *format, ...)
{
    if (min_level > level::DEBUG)
        return;
    va_list list;
    va_start(list, format);
    log_internal(level::DEBUG, format, list);
    va_end(list);
}

void info(const char *format, ...)
{
    if (min_level > level::INFO)
        return;
    va_list list;
    va_start(list, format);
    log_internal(level::INFO, format, list);
    va_end(list);
}

void warning(const char *format, ...)
{
    if (min_level > level::WARNING)
        return;
    va_list list;
    va_start(list, format);
    log_internal(level::WARNING, format, list);
    va_end(list);
}

void error(const char *format, ...)
{
    if (min_level > level::ERROR)
        return;
    va_list list;
    va_start(list, format);
    log_internal(level::ERROR, format, list);
    va_end(list);
}

}


