/*
 * hook.cpp
 *
 *  Created on: Nov 19, 2017
 *      Author: nullifiedcat
 */

#include "hook.hpp"

#include <string.h>
#include <stdlib.h>

namespace hook
{

unsigned count_methods(method_table_t table)
{
    unsigned int i = -1;
    do
        ++i;
    while (table[i]);
    return i;
}

table_ref_t get_vmt(ptr_t inst, uintptr_t offset)
{
    return *reinterpret_cast<table_ptr_t>((uintptr_t) inst + offset);
}

bool is_hooked(ptr_t inst, uintptr_t offset)
{
    return get_vmt(inst, offset)[-1] == (method_t) GUARD;
}

vmt_hook::~vmt_hook()
{
    release();
}

void vmt_hook::init(ptr_t inst, uintptr_t offset)
{
    release();
    vtable_ptr      = &get_vmt(inst, offset);
    vtable_original = *vtable_ptr;
    int mc          = count_methods(vtable_original);
    vtable_hooked = static_cast<method_table_t>(calloc(mc + 3, sizeof(ptr_t)));
    memcpy(&vtable_hooked[2], vtable_original, sizeof(ptr_t) * mc);
    vtable_hooked[0] = this;
    vtable_hooked[1] = (method_t) GUARD;
}

void vmt_hook::hook(method_t func, uintptr_t idx)
{
    vtable_hooked[2 + idx] = func;
}

void vmt_hook::apply()
{
    *vtable_ptr = &vtable_hooked[2];
}

void vmt_hook::release()
{
    if (vtable_ptr && *vtable_ptr == &vtable_hooked[2])
    {
        if ((*vtable_ptr)[-1] == (method_t) GUARD)
        {
            *vtable_ptr = vtable_original;
        }
        free(vtable_hooked);
        vtable_ptr      = nullptr;
        vtable_hooked   = nullptr;
        vtable_original = nullptr;
    }
}

method_t vmt_hook::get(uintptr_t idx) const
{
    return vtable_original[idx];
}
}
