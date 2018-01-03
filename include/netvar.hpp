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
public:
    map_t nodes_{};
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
    void init_offset(temporary_netvar_tree& tree)
    {
        offset_ = 0;

        temporary_netvar_tree::map_t *current = &tree.nodes_;

        while (!location_.empty())
        {
            auto next = location_.front();

            // Will throw an exception if tree does not contain the netvar
            temporary_netvar_tree::node& node = *current->at(next);

            offset_ += node.prop->GetOffset();
            current = &node.nodes;

            location_.pop();
        }
    }
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
    void init();
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
