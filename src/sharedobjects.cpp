/*
 * sharedobjects.cpp
 *
 *  Created on: Nov 19, 2017
 *      Author: nullifiedcat
 */

#include "sharedobjects.hpp"
#include "tools.hpp"
#include "log.hpp"

#include <fstream>
#include <thread>
#include <unistd.h>
#include <dlfcn.h>
#include <link.h>

namespace so {

bool object_full_path(std::string& name, std::string& out_full_path)
{
    std::ifstream maps(tools::makestring("/proc/", getpid(), "/maps"), std::ios::in);
    if (maps.bad())
    {
        return false;
    }
    for (std::string line; getline(maps, line); )
    {
        size_t s_path = line.find_first_of('/');
        size_t s_name = line.find_last_of('/');
        if (s_name == std::string::npos || s_path == std::string::npos)
        {
            continue;
        }
        if (0 == name.compare(0, std::string::npos, line, s_name + 1, name.length()))
        {
            out_full_path = line.substr(s_path);
            if (out_full_path.back() == '\n')
            {
                out_full_path.pop_back();
            }
            return true;
        }
    }
    return false;
}

shared_object::shared_object(const std::string& name, bool is_interface_factory):
        name_(name), factory_(is_interface_factory)
{
    load();
}

void shared_object::load()
{
    while (!object_full_path(name_, path_))
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    lmap = (link_map *)dlopen(path_.c_str(), RTLD_NOLOAD);
    while (lmap == nullptr)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        char *error = dlerror();
        if (error)
        {
            log::error("dlerror: %s", error);
        }
        lmap = (link_map *)dlopen(path_.c_str(), RTLD_NOLOAD);
    }

    log::debug("Shared object %s loaded at 0x%08x", name_.c_str(), lmap->l_addr);
    if (factory_)
    {
        create_interface_fn = reinterpret_cast<CreateInterface_t>(dlsym(lmap, "CreateInterface"));
        if (create_interface_fn == nullptr)
        {
            log::error("Failed to create interface factory for %s", name_.c_str());
        }
    }
}


shared_object& steamclient()
{
    static shared_object object("steamclient.so", true);
    return object;
}

shared_object& client()
{
    static shared_object object("client.so", true);
    return object;
}

shared_object& engine()
{
    static shared_object object("engine.so", true);
    return object;
}

shared_object& vstdlib()
{
    static shared_object object("libvstdlib.so", true);
    return object;
}

shared_object& tier0()
{
    static shared_object object("libtier0.so", false);
    return object;
}

shared_object& inputsystem()
{
    static shared_object object("inputsystem.so", true);
    return object;
}

shared_object& materialsystem()
{
    static shared_object object("materialsystem.so", true);
    return object;
}

shared_object& vguimatsurface()
{
    static shared_object object("vguimatsurface.so", true);
    return object;
}

shared_object& vgui2()
{
    static shared_object object("vgui2.so", true);
    return object;
}

shared_object& studiorender()
{
    static shared_object object("studiorender.so", true);
    return object;
}

shared_object& libsdl()
{
    static shared_object object("libSDL2-2.0.so.0", false);
    return object;
}

}



