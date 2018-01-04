/*
 * usercmd.h
 *
 *  Created on: Jan 4, 2018
 *      Author: nullifiedcat
 */

#pragma once

class CUserCmd
{
public:
    virtual ~CUserCmd() {};
    int command_number;
    int tick_count;
    Vector viewangles;
    float forwardmove;
    float sidemove;
    float upmove;
    int buttons;
    uint8_t impulse;
    int weaponselect;
    int weaponsubtype;
    int random_seed;
    short mousedx;
    short mousedy;
    bool hasbeenpredicted;
};


