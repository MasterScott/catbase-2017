/*
 * log.hpp
 *
 *  Created on: Nov 18, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include <string>

/*
 * The reason I use macros instead of functions is because with macros, compiler won't embed unneeded strings in the binary, that is important for debug logging.
 * You wouldn't want plaintext description of what your functions do in the resulting library, it would make it really easy to reverse.
 * You should change the LOG_LEVEL if you want.
 *
 * And #defines don't like ::'s inside - so a global enum is used instead of an enum class.
 */

enum catbase_log_level
{
    CBLL_NONE,
    CBLL_ERROR,
    CBLL_WARNING,
    CBLL_INFO,
    CBLL_DEBUG,
    CBLL_SILLY
};

namespace catbase_logging
{

void setup(std::string filename);

void log_internal(catbase_log_level lvl, const char *format, ...);

}

#ifndef CATBASE_LOG_LEVEL

#if DEBUG_BUILD
#       define CATBASE_LOG_LEVEL CBLL_DEBUG
#else
#       define CATBASE_LOG_LEVEL CBLL_NONE
#endif

#endif

#if CATBASE_LOG_LEVEL == CBLL_NONE
#       define CATBASE_LOG_SETUP(filename)
#else
#       define CATBASE_LOG_SETUP(filename) \
		catbase_logging::setup(filename)
#endif

#if CATBASE_LOG_LEVEL >= CBLL_SILLY
#       define LOG_SILLY(...) catbase_logging::log_internal(CBLL_SILLY, __VA_ARGS__)
#else
#       define LOG_SILLY(...)
#endif

#if CATBASE_LOG_LEVEL >= CBLL_DEBUG
#       define LOG_DEBUG(...) catbase_logging::log_internal(CBLL_DEBUG, __VA_ARGS__)
#else
#       define LOG_DEBUG(...)
#endif

#if CATBASE_LOG_LEVEL >= CBLL_INFO
#       define LOG_INFO(...) catbase_logging::log_internal(CBLL_INFO, __VA_ARGS__)
#else
#       define LOG_INFO(...)
#endif

#if CATBASE_LOG_LEVEL >= CBLL_WARNING
#       define LOG_WARNING(...) catbase_logging::log_internal(CBLL_WARNING, __VA_ARGS__)
#else
#       define LOG_WARNING(...)
#endif

#if CATBASE_LOG_LEVEL >= CBLL_ERROR
#       define LOG_ERROR(format, ...) catbase_logging::log_internal(CBLL_ERROR, format, __VA_ARGS__)
#else
#       define LOG_ERROR(format, ...)
#endif
