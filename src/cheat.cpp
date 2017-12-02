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

namespace cheat
{

void init()
{
    log::setup(log::level::DEBUG, true, "/tmp/catbase-%USER%.log");
    log::info("Welcome!");
    log::debug("Trying to load some shared objects");
    I<void>::init(so::client(), "VClientEntityList", 0);
    log::debug("%p", I<void>()());
}

void shutdown()
{
    log::warning("Shutting down!");
}

}
