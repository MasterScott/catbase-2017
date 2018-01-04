/*
 * interfaces.hpp
 *
 *  Created on: Dec 2, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include "sharedobjects.hpp"
#include "log.hpp"

void interfaces_init_all();

template <typename T> class I
{
public:
    inline static void init(const so::shared_object &object,
                            const std::string &name, int version)
    {
        if (interface_pointer_)
            return;

        char ifname[name.length() + 4];
        for (int i = version; i < 100; i++)
        {
            snprintf(ifname, sizeof(ifname), "%s%03d", name.c_str(), i);
            interface_pointer_ = reinterpret_cast<T *>(
                object.create_interface_fn(ifname, nullptr));
            if (interface_pointer_ != nullptr)
                return;
        }

        LOG_ERROR("Failed to create interface '%s'", name.c_str());
    }
    inline operator T *() const
    {
        return interface_pointer_;
    }
    inline T *operator()() const
    {
        return interface_pointer_;
    }
    inline T *operator->() const
    {
        return interface_pointer_;
    }
    inline void operator=(T *pointer)
    {
        interface_pointer_ = pointer;
    }

public:
    static T *interface_pointer_;
};

template <typename T> T *I<T>::interface_pointer_;
