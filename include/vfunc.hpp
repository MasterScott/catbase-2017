/*
 * vfunc.hpp
 *
 *  Created on: Nov 19, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include <stdint.h>

template <typename T> inline T vfunc(void *object, unsigned index)
{
    uintptr_t *vtable = *(uintptr_t **) object;
    return T(vtable[index]);
}
