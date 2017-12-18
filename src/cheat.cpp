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

namespace cheat
{

void init()
{
    log::setup(log::level::DEBUG, true, "/tmp/catbase-%USER%.log");
    log::info("Welcome!");
    log::debug("Trying to load some shared objects");
    I<void>::init(so::client(), "VClientEntityList", 0);

    int *g_pPredictionRandomSeed = *(
        int *
            *) (signature::signature(
                    "A3 ? ? ? ? C3 8D 74 26 00 B8 FF FF FF FF 5D A3 ? ? ? ? C3")
                    .scan(so::client()) +
                1);
    log::debug("pRandom seed: %08x", g_pPredictionRandomSeed);
    log::debug("Random seed: %d", *g_pPredictionRandomSeed);
    log::debug("%p", I<void>()());
}

void shutdown()
{
    log::warning("Shutting down!");
}
}
