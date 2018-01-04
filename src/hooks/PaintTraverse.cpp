/*
 * PaintTraverse.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: nullifiedcat
 */

#include "hooks/hooks.hpp"
#include "hook.hpp"
#include "interfaces.hpp"
#include "visual/draw.hpp"

#include <vgui/ISurface.h>

vgui::VPANEL panel_top = 0,
             panel_focus = 0;

void hooks::PaintTraverse(vgui::IPanel *this_, vgui::VPANEL vguiPanel, bool forceRepaint, bool allowForce)
{
    typedef void(*PaintTraverse_t)(vgui::IPanel *, vgui::VPANEL, bool, bool);

    if (!panel_top)
    {
        const char *name = I<vgui::IPanel>()->GetName(vguiPanel);
        if (strlen(name) > 4)
        {
            if (name[0] == 'M' && name[3] == 'S')
            {
                panel_top = vguiPanel;
            }
        }
    }
    if (!panel_focus)
    {
        const char *name = I<vgui::IPanel>()->GetName(vguiPanel);
        if (strlen(name) > 5)
        {
            if (name[0] == 'F' && name[5] == 'O')
            {
                panel_focus = vguiPanel;
            }
        }
    }

    hook::original<PaintTraverse_t>(this_, 42)(this_, vguiPanel, forceRepaint, allowForce);

    if (vguiPanel != panel_focus)
        return;

    I<vgui::IPanel>()->SetTopmostPopup(panel_focus, true);

    draw_api::draw_begin();

    draw_api::draw_string(200, 200, "Welcome to catbase!", draw::fonts::tf2build_large, colors::pink);

    draw_api::draw_end();

}
