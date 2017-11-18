/*
 * cheat.cpp
 *
 *  Created on: Nov 19, 2017
 *      Author: nullifiedcat
 */

#include "cheat.hpp"
#include "log.hpp"

namespace cheat
{

void init()
{
    log::setup(log::level::DEBUG, true, "/tmp/catbase-%USER%.log");
    log::debug("Welcome!");
    log::info("Welcome!");
    log::warning("Welcome!");
    log::error("Welcome!");
}

void shutdown()
{
    log::warning("Shutting down!");
}

}
