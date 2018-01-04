/*
 * netvar.hpp
 *
 *  Created on: Dec 30, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include <queue>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <iostream>

#include <dt_recv.h>

class RecvTable;
class RecvProp;

namespace netvar
{

namespace internal
{

class netvar_base;

inline std::queue<netvar_base *>& init_list()
{
    static std::queue<netvar_base *> object{};
    return object;
}

class temporary_netvar_tree
{
public:
    class node;
    typedef std::unordered_map<std::string, std::unique_ptr<node>> map_t;
    class node
    {
    public:
        map_t nodes{};
        RecvProp *prop{ nullptr };
    };
public:
    temporary_netvar_tree();
public:
    map_t table_to_map(RecvTable *table);
    void dump(std::ostream& stream);
    void dump_recursive(std::ostream& stream, int depth, int accumulated, const map_t& map);
public:
    std::unordered_map<std::string, map_t> nodes_{};
};

class netvar_base
{
public:
    inline netvar_base(std::initializer_list<std::string> location)
        : location_{ location }
    {
        init_list().push(this);
    }
    public:
public:
    inline uintptr_t offset() const
    {
        return offset_;
    }
    void init_offset(temporary_netvar_tree& tree);
protected:
    uintptr_t offset_{ 0 };
    std::queue<std::string> location_{};
};

template<typename T>
class netvar: public netvar_base
{
public:
    template<typename X>
    inline T& operator()(X* instance) const
    {
        return *reinterpret_cast<T*>(uintptr_t(instance) + offset());
    }
protected:
};

class storage
{
public:
    storage() = default;
public:
    temporary_netvar_tree init();
public:
    struct
    {
        netvar<int> team{ {"DT_BaseEntity", "m_iTeamNum"} };
    } entity;

    struct
    {
        netvar<int> health{ {"DT_BasePlayer", "m_iHealth"} };
        netvar<uint32_t> flags{ {"DT_BasePlayer", "m_iHealth"} };
        netvar<uint8_t> life_state{ {"DT_BasePlayer", "m_lifeState"} };
    } player;
};

}

}

extern netvar::internal::storage netvars;
