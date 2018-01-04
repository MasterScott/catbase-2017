/*
 * cheat.cpp
 *
 *  Created on: Nov 19, 2017
 *      Author: nullifiedcat
 */

#include "cheat.hpp"
#include "log.hpp"
#include "sharedobjects.hpp"
#include "interfaces.hpp"
#include "signature.hpp"
#include "netvar.hpp"
#include "hooks/hooks.hpp"
#include "visual/draw.hpp"

#include <fstream>
#include <unistd.h>

#include <cdll_int.h>
#include <icliententitylist.h>

namespace cheat
{

void init()
{
    CATBASE_LOG_SETUP("/tmp/catbase-%USER%.log");
    LOG_DEBUG("Initializing interfaces");

    interfaces_init_all();

    {
        auto tree = netvars.init();
        std::ofstream dump("/tmp/catbase-netvar-dump.log");
        if (dump)
            tree.dump(dump);
    }

    LOG_DEBUG("Initializing hooks");
    hooks::init();
    LOG_DEBUG("Initializing drawing");
    draw::init();

    LOG_DEBUG("Init done");

    pause();
}

void shutdown()
{
    LOG_WARNING("Shutting down now");
}
}
