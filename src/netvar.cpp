/*
 * netvar.cpp
 *
 *  Created on: Dec 30, 2017
 *      Author: nullifiedcat
 */

#include "netvar.hpp"
#include "interfaces.hpp"
#include "log.hpp"

#include <cdll_int.h>
#include <client_class.h>
#include <dt_recv.h>

namespace netvar
{

namespace internal
{

temporary_netvar_tree::temporary_netvar_tree()
{
    auto *current = I<IBaseClientDLL>()->GetAllClasses();

    while (current != nullptr)
    {
        nodes_[std::string(current->m_pRecvTable->m_pNetTableName)] = table_to_map(current->m_pRecvTable);
        current = current->m_pNext;
    }
}


void temporary_netvar_tree::dump(std::ostream& stream)
{
    for (const auto& i : nodes_)
    {
        stream << i.first << '\n';
        dump_recursive(stream, 1, 0, i.second);
        stream << "\n\n";
    }
}

static const char *sendproptypenames[] = {
        "Int",
        "Float",
        "Vector",
        "VectorXY",
        "String",
        "Array",
        "Table",
        nullptr
};

void temporary_netvar_tree::dump_recursive(std::ostream& stream, int depth, int accumulated, const temporary_netvar_tree::map_t& map)
{
    for (const auto& i : map)
    {
        const auto& node = i.second;

        if (isdigit(node->prop->GetName()[0]))
            continue;

        stream << std::string(depth, '\t') << node->prop->GetName() << " [" << sendproptypenames[node->prop->GetType()] << "]: " << std::hex << accumulated + node->prop->GetOffset() << '\n';

        if (node->prop->m_RecvType == SendPropType::DPT_DataTable)
        {
            dump_recursive(stream, depth + 1, accumulated + node->prop->GetOffset(), node->nodes);
        }
    }
}

temporary_netvar_tree::map_t temporary_netvar_tree::table_to_map(RecvTable *table)
{
    map_t result{};

    for (auto i = 0; i < table->m_nProps; ++i)
    {
        auto& prop = table->m_pProps[i];

        std::unique_ptr<temporary_netvar_tree::node> node = std::make_unique<temporary_netvar_tree::node>();

        if (prop.m_RecvType == SendPropType::DPT_DataTable)
        {
            node->nodes = table_to_map(prop.GetDataTable());
        }

        node->prop = &prop;
        result.insert(std::make_pair(std::string(prop.m_pVarName), std::move(node)));
    }

    return result;
}

void netvar_base::init_offset(temporary_netvar_tree& tree)
{
    offset_ = 0;

    auto& datatable = tree.nodes_.at(location_.front());
    location_.pop();

    temporary_netvar_tree::map_t *current = &datatable;

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

temporary_netvar_tree storage::init()
{
    LOG_DEBUG("Initializing netvar tree");

    temporary_netvar_tree tree{};

    while (!init_list().empty())
    {
        auto netvar = init_list().front();

        try
        {
            netvar->init_offset(tree);
        }
        catch (std::exception& ex)
        {
            LOG_ERROR("Error while initializing NetVar: %s", ex.what());
        }

        init_list().pop();
    }

    return tree;
}

}

}

netvar::internal::storage netvars{};
