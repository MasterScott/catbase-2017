/*
 * cheat.cpp
 *
 *  Created on: Nov 19, 2017
 *      Author: nullifiedcat
 */

#include "cheat.hpp"
#include "log.hpp"
#include "sharedobjects.hpp"

namespace cheat
{

void init()
{
    log::setup(log::level::DEBUG, true, "/tmp/catbase-%USER%.log");
    log::info("Welcome!");
    log::debug("Trying to load some shared objects");
    log::debug("client.so:CreateInterface: %p", so::client().create_interface_fn);
}

void shutdown()
{
    log::warning("Shutting down!");
}

}
