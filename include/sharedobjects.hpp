/*
 * sharedobjects.hpp
 *
 *  Created on: Nov 19, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include <string>
#include <vector>

struct link_map;

namespace so {

bool object_full_path(std::string& name, std::string& out_full_path);

class shared_object {
public:
    typedef void *(*CreateInterface_t)(const char *, int *);
public:
    shared_object(const std::string& name, bool is_interface_factory);
protected:
    void load();
public:
    std::string name_;
    std::string path_;

    bool factory_{ false };
    bool loaded_{ false };

    CreateInterface_t create_interface_fn{ nullptr };
    link_map *lmap{ nullptr };
};


shared_object& steamclient();
shared_object& client();
shared_object& engine();
shared_object& vstdlib();
shared_object& tier0();
shared_object& inputsystem();
shared_object& materialsystem();
shared_object& vguimatsurface();
shared_object& vgui2();
shared_object& studiorender();
shared_object& libsdl();

}


