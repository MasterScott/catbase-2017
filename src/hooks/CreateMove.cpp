/*
 * CreateMove.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: nullifiedcat
 */

#include "hooks/hooks.hpp"
#include "hook.hpp"
#include "interfaces.hpp"

#include <cdll_int.h>

#include "sdk/in_buttons.h"

bool hooks::CreateMove(IClientMode *this_, float flInputSampleTime, CUserCmd *cmd)
{
    typedef bool(*CreateMove_t)(IClientMode *, float, CUserCmd *);

    if (cmd)
    {
        cmd->forwardmove = -cmd->forwardmove;
        cmd->sidemove = -cmd->sidemove;
    }

    return hook::original<CreateMove_t>(this_, 22)(this_, flInputSampleTime, cmd);
}


