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
#include <dt_recv.h>

namespace netvar
{

namespace internal
{

temporary_netvar_tree::temporary_netvar_tree()
{
    auto *begin= I<IBaseClientDLL>()->GetAllClasses();


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

void storage::init()
{
    LOG_DEBUG("Initializing netvar tree");

    temporary_netvar_tree tree{};

    while (!init_list().empty())
    {
        auto netvar = init_list().front();

        netvar->

        init_list().pop();
    }
}

}

}

netvar::internal::storage netvars{};
