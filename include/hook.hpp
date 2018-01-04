/*
 * hook.hpp
 *
 *  Created on: Nov 19, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include <stdint.h>

#include "log.hpp"

namespace hook
{

typedef void *ptr_t;
typedef void *method_t;
typedef method_t *method_table_t;
typedef method_table_t *table_ptr_t;
typedef method_table_t &table_ref_t;

constexpr uintptr_t GUARD = 0xD34DC477;

template<typename T, typename X>
inline T original(X *instance, unsigned index)
{
    const method_table_t active = *reinterpret_cast<table_ptr_t>(uintptr_t(instance));

    if (active[-1] != method_t(GUARD))
    {
        LOG_ERROR("Tried to call original function on non-hooked instance. Fatal.");
        // C++ does not allow me to reinterpret_cast a nullptr into function pointer
        union
        {
            T fn;
            nullptr_t nfn;
        } u;
        u.nfn = nullptr;
        // Make the game crash
        return u.fn;
    }

    return reinterpret_cast<T>(reinterpret_cast<method_table_t>(active[-2])[index]);
}

class vmt_hook
{
public:
    vmt_hook() = default;
    ~vmt_hook();

public:
    void init(ptr_t inst, uintptr_t offset = 0);
    void hook(method_t func, uintptr_t idx);
    void apply();
    method_t get(uintptr_t idx) const;
    void release();

public:
    ptr_t object{ nullptr };
    table_ptr_t vtable_ptr{ nullptr };
    method_table_t vtable_original{ nullptr };
    method_table_t vtable_hooked{ nullptr };
};
}
