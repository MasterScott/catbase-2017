/*
 * interfaces.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: nullifiedcat
 */

#include "interfaces.hpp"
#include "signature.hpp"
#include "log.hpp"

class IClientEntityList;
class IVEngineClient013;
class IBaseClientDLL;
class IClientMode;

namespace vgui { class IPanel; class ISurface; }

void interfaces_init_all()
{
    I<IClientEntityList>::init(so::client(), "VClientEntityList", 0);
    I<IVEngineClient013>::init(so::engine(), "VEngineClient", 13);
    I<IBaseClientDLL>::init(so::client(), "VClient", 0);
    I<IClientMode>() = **signature::signature("A3 ? ? ? ? E8 ? ? ? ? 8B 10 89 04 24 C7 44 24 04").scan<IClientMode **>(so::client(), 1);
    I<vgui::IPanel>::init(so::vgui2(), "VGUI_Panel", 0);
    I<vgui::ISurface>::init(so::vguimatsurface(), "VGUI_Surface", 0);
}


