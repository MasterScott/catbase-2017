/*
 * hooks.hpp
 *
 *  Created on: Nov 19, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include <vgui/IPanel.h>
#include <cdll_int.h>
#include "sdk/usercmd.h"
class IClientMode;

namespace hooks
{

void PaintTraverse(vgui::IPanel *this_, vgui::VPANEL vguiPanel, bool forceRepain, bool allowForce);
bool CreateMove(IClientMode *this_, float flInputSampleTime, CUserCmd *cmd);

void init();

}
