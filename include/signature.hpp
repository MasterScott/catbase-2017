/*
 * signature.hpp
 *
 *  Created on: May 27, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include "sharedobjects.hpp"

#include <stdint.h>
#include <string>
#include <vector>

namespace signature
{

constexpr char __attribute__((pure)) chtohex(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return 10 + (c - 'a');
    if (c >= 'A' && c <= 'F')
        return 10 + (c - 'A');
    return 0;
}

class signature
{
public:
    signature() = delete;
    /*
     * Convert from IDA style signature ("00 01 02 ?? AB")
     * to a signature_t
     */
    signature(const std::string &ida);
    /*
     * Create signature from raw bytes ("\x00\x01\x02\x00\xAB", "xxx?x")
     */
    signature(const uint8_t *bytes, const char *mask);

public:
    uintptr_t scan(uintptr_t start, uintptr_t length);

    template <typename T>
    T *scan(const so::shared_object &object, uintptr_t offset)
    {
        uintptr_t found = scan(object.text_begin_, object.text_end_);
        if (found)
            return reinterpret_cast<T *>(found + offset);
        return 0;
    }

protected:
    std::vector<uint8_t> data_{};
    std::vector<bool> mask_{};
};
}
