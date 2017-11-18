/*
 * somain.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: nullifiedcat
 */

#include <thread>

#include "log.hpp"

std::thread main_thread;

void base_main()
{
    log::setup(log::level::DEBUG, true, "/tmp/catbase-%USER%.log");
    log::info("Welcome!");
}

void __attribute__((constructor)) attach()
{
    main_thread = std::thread { base_main };
}

void __attribute__((destructor)) detach()
{
    log::info("Unloading!");
}
