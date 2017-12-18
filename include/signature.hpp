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
    static constexpr uintptr_t not_found = 0xFFFFFFFF;

public:
    signature() = delete;
    /*
     * Convert from IDA style signature ("00 01 02 ?? AB")
     * to a signature_t
     */
    signature(const std::string &ida);
    /*
     * Create signature from raw bytes ("\x00 \x01 \x02 \x00 \xAB", "xxx?x")
     */
    signature(const uint8_t *bytes, const char *mask);

public:
    uintptr_t scan(uintptr_t start, uintptr_t length);
    uintptr_t scan(const so::shared_object &object);

protected:
    std::vector<uint8_t> data_{};
    std::vector<bool> mask_{};
};
}
