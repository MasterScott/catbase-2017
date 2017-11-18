/*
 * somain.cpp
 *
 *  Created on: Nov 18, 2017
 *      Author: nullifiedcat
 */

#include <thread>

std::thread main_thread;

void base_main()
{

}

void __attribute__((constructor)) attach()
{
    main_thread = std::thread { base_main };
}

void __attribute__((destructor)) detach()
{

}
