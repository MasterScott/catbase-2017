/*
 * hook.cpp
 *
 *  Created on: Nov 19, 2017
 *      Author: nullifiedcat
 */

#include "hook.hpp"
#include "log.hpp"

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

table_ref_t get_vmt(ptr_t inst, uintptr_t offset = 0)
{
    return *reinterpret_cast<table_ptr_t>((uintptr_t) inst + offset);
}

inline bool is_hooked(ptr_t inst, uintptr_t offset = 0)
{
    return get_vmt(inst, offset)[-1] == (method_t) GUARD;
}

vmt_hook::~vmt_hook()
{
    release();
}

void vmt_hook::init(ptr_t inst, uintptr_t offset)
{
    vtable_ptr      = &get_vmt(inst, offset);
    vtable_original = *vtable_ptr;
    int mc          = count_methods(vtable_original);
    LOG_DEBUG("Hooking %08x with %d methods, vtable at %08x %08x", inst, mc, vtable_original, vtable_ptr);
    vtable_hooked = static_cast<method_table_t>(calloc(mc + 4, sizeof(ptr_t)));
    memcpy(&vtable_hooked[3], vtable_original, sizeof(ptr_t) * mc);
    vtable_hooked[0] = this;
    vtable_hooked[1] = vtable_original;
    vtable_hooked[2] = (method_t) GUARD;
}

void vmt_hook::hook(method_t func, uintptr_t idx)
{
    LOG_DEBUG("Replacing method %u (%08x) with %08x", idx, vtable_original[idx], func);
    vtable_hooked[3 + idx] = func;
}

void vmt_hook::apply()
{
    LOG_DEBUG("Applied hook");
    *vtable_ptr = &vtable_hooked[3];
}

void vmt_hook::release()
{
    if (vtable_ptr && *vtable_ptr == &vtable_hooked[3])
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
