/*
 * signature.cpp
 *
 *  Created on: May 27, 2017
 *      Author: nullifiedcat
 */

#include "signature.hpp"
#include "log.hpp"

#include <sys/uio.h>

#include <vector>
#include <memory>
#include <stdio.h>
#include <string.h>

namespace signature
{

signature::signature(const std::string &ida)
{
    for (size_t i = 0; i < ida.length(); i++)
    {
        char ch = ida.at(i);
        if (ch == '?')
        {
            if (i < ida.length() - 1)
            {
                if (ida.at(i + 1) == '?')
                    ++i;
            }
            data_.push_back(0);
            mask_.push_back(false);
            ++i;
            continue;
        }
        if (ch == ' ')
            continue;
        if (i < ida.length() - 1)
        {
            char lower = ida.at(i + 1);
            char byte  = (chtohex(ch) << 4) | chtohex(lower);
            data_.push_back(byte);
            mask_.push_back(true);
            ++i;
            continue;
        }
    }
}

signature::signature(const uint8_t *bytes, const char *mask)
{
    for (size_t i = 0; i < strlen(mask); i++)
    {
        if (mask_[i] != '?')
        {
            data_.push_back(bytes[i]);
            mask_.push_back(true);
        }
        else
        {
            data_.push_back(0);
            mask_.push_back(false);
        }
    }
}

uintptr_t signature::scan(uintptr_t start, uintptr_t end)
{
    log::debug("scanning from %p to %p for %u bytes", start, end, data_.size());
    size_t found = 0;
    for (; start < end; start++)
    {
        if (mask_.at(found))
        {
            if (*(uint8_t *) start == data_.at(found))
                ++found;
            else
                found = 0;
        }
        else
        {
            ++found;
        }
        if (found == data_.size())
        {
            return start - found + 1;
        }
    }
    return 0;
}
}
