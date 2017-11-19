/*
 * hook.hpp
 *
 *  Created on: Nov 19, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include <stdint.h>

namespace hook {

typedef void *ptr_t;
typedef void *method_t;
typedef method_t *method_table_t;
typedef method_table_t *table_ptr_t;
typedef method_table_t& table_ref_t;

unsigned count_methods(method_table_t table);
table_ref_t get_vmt(ptr_t inst, uintptr_t offset = 0);
bool is_hooked(ptr_t inst, uintptr_t offset = 0);

constexpr uintptr_t GUARD = 0xD34DC477;

class vmt_hook {
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
