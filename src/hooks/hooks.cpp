/*
 * hooks.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: nullifiedcat
 */

#include "hooks/hooks.hpp"
#include "hook.hpp"
#include "interfaces.hpp"

namespace hooks
{

hook::vmt_hook ipanel{};
hook::vmt_hook clientmode{};

void init()
{
    ipanel.init(I<vgui::IPanel>());
    ipanel.hook(hook::method_t(PaintTraverse), 42);
    ipanel.apply();

    clientmode.init(I<IClientMode>());
    clientmode.hook(hook::method_t(CreateMove), 22);
    clientmode.apply();
}

}
