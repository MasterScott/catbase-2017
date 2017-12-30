/*
 * somain.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: nullifiedcat
 */

#include <thread>
#include <atomic>

#include "cheat.hpp"

#include <stdio.h>

std::thread main_thread;

void cheat_main_thread()
{
    cheat::init();
}

void __attribute__((constructor)) attach()
{
    main_thread = std::thread{ cheat_main_thread };
}

void __attribute__((destructor)) detach()
{
    cheat::shutdown();
}
