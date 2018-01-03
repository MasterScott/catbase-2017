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

#include <cdll_int.h>
#include <icliententitylist.h>

namespace cheat
{

void init()
{
    CATBASE_LOG_SETUP("/tmp/catbase-%USER%.log");
    LOG_INFO("Welcome!");
    LOG_SILLY("This is a test! %d %s", 123, "Test!");
    LOG_DEBUG("Loading some shared objects");

    I<IClientEntityList>::init(so::client(), "VClientEntityList", 0);
    I<IVEngineClient013>::init(so::engine(), "VEngineClient", 13);
    I<IBaseClientDLL>::init(so::client(), "VClient", 0);

    netvars.init();

    LOG_DEBUG("Health: %u", netvars.player.health.offset());



    int *g_pPredictionRandomSeed =
        *(signature::signature(
              "A3 ? ? ? ? C3 8D 74 26 00 B8 FF FF FF FF 5D A3 ? ? ? ? C3")
              .scan<int *>(so::client(), 1));
}

void shutdown()
{
    LOG_WARNING("Shutting down now");
}
}
