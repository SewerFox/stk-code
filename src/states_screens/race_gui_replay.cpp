//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2004-2015 Steve Baker <sjbaker1@airmail.net>
//  Copyright (C) 2006-2015 Joerg Henrichs, SuperTuxKart-Team, Steve Baker
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "states_screens/race_gui_replay.hpp"

using namespace irr;

#include <algorithm>
#include <limits>

#include "config/user_config.hpp"
#include "font/font_drawer.hpp"
#include "graphics/camera/camera.hpp"
#include "graphics/central_settings.hpp"
#include "graphics/2dutils.hpp"
#ifndef SERVER_ONLY
#include "graphics/glwrap.hpp"
#endif
#include "graphics/irr_driver.hpp"
#include "graphics/material.hpp"
#include "guiengine/engine.hpp"
#include "guiengine/modaldialog.hpp"
#include "guiengine/scalable_font.hpp"
#include "input/device_manager.hpp"
#include "input/input_device.hpp"
#include "input/input_manager.hpp"
#include "io/file_manager.hpp"
#include "items/powerup_manager.hpp"
#include "items/projectile_manager.hpp"
#include "karts/kart.hpp"
#include "karts/controller/controller.hpp"
#include "karts/kart_properties.hpp"
#include "karts/kart_properties_manager.hpp"
#include "modes/linear_world.hpp"
#include "modes/world.hpp"
#include "modes/soccer_world.hpp"
#include "network/protocols/client_lobby.hpp"
#include "replay/replay_control.hpp"
#include "states_screens/race_gui_multitouch.hpp"
#include "utils/constants.hpp"
#include "utils/string_utils.hpp"
#include "utils/translation.hpp"

#include <algorithm>

#include <IrrlichtDevice.h>

/** The constructor is called before anything is attached to the scene node.
 *  So rendering to a texture can be done here. But world is not yet fully
 *  created, so only the race manager can be accessed safely.
 */
RaceGUIReplay::RaceGUIReplay()
{
    m_enabled = true;
    
    if (UserConfigParams::m_artist_debug_mode && UserConfigParams::m_hide_gui)
        m_enabled = false;

    initSize();
    bool multitouch_enabled = (UserConfigParams::m_multitouch_active == 1 &&
                               irr_driver->getDevice()->supportsTouchDevice()) ||
                               UserConfigParams::m_multitouch_active > 1;
    
    if (multitouch_enabled && UserConfigParams::m_multitouch_draw_gui &&
        RaceManager::get()->getNumLocalPlayers() == 1)
    {
        m_multitouch_gui = new RaceGUIMultitouch(this);
    }

    drawReplayGUI();
    // m_speed_meter_icon = irr_driver->getTexture(FileManager::GUI_ICON, "speedback.png");
}   // RaceGUIReplay

// ----------------------------------------------------------------------------
/** Called when loading the race gui or screen resized. */
void RaceGUIReplay::initSize()
{
    RaceGUIBase::initSize();
    // Determine maximum length of the rank/lap text, in order to
    // align those texts properly on the right side of the viewport.
    gui::ScalableFont* font = GUIEngine::getHighresDigitFont();
    core::dimension2du area = font->getDimension(L"99:99.999");
    m_font_height = area.Height;
}   // initSize

//-----------------------------------------------------------------------------
RaceGUIReplay::~RaceGUIReplay()
{
    delete m_multitouch_gui;
}   // ~RaceGUIReplay


//-----------------------------------------------------------------------------
void RaceGUIReplay::init()
{
    RaceGUIBase::init();
}   // init

//-----------------------------------------------------------------------------
/** Reset the gui before a race. It initialised all rank animation related
 *  values back to the default.
 */
void RaceGUIReplay::reset()
{
    RaceGUIBase::reset();
}  // reset

//-----------------------------------------------------------------------------
/** Draws one of the replay control menu's lines.
 */
void RaceGUIReplay::drawReplayMenuLine(const core::stringw& text, int y, int x, bool hcenter)
{
    core::rect<s32> pos(x,
                        y,
                        irr_driver->getActualScreenSize().Width,
                        y + irr_driver->getActualScreenSize().Height*3/100);

    gui::ScalableFont* font = GUIEngine::getFont();
    font->draw(text.c_str(), pos, video::SColor(255, 255, 255, 255),
               hcenter, false, NULL, true);
}   // drawReplayMenuLine

//-----------------------------------------------------------------------------
/** Gets a key bound to a certain action
 */
static core::stringw getKeyBinding(PlayerAction action)
{
    InputDevice* device = input_manager->getDeviceManager()->getLatestUsedDevice();
    if (device != NULL)
    {
        DeviceConfig* config = device->getConfiguration();
        return config->getBindingAsString(action);
    }
    else return "";
}   // getKeyBinding

//-----------------------------------------------------------------------------
/** Draws the replay control menu.
 */
void RaceGUIReplay::drawReplayGUI()
{
    ReplayControl* rc = ReplayControl::get();
    int height = irr_driver->getActualScreenSize().Height;
    int width = irr_driver->getActualScreenSize().Width;
    int y = height*20/100;
    int x = width*77/100;

    gui::ScalableFont* font = GUIEngine::getFont();
    font->setScale(1.0f);
    font->setBlackBorder(true);

    drawReplayMenuLine(_("--Replay Controls--"), y, x, true);

    y = height*24/100;

    drawReplayMenuLine(_("[%s] to pause", getKeyBinding(PA_FIRE)), y, x,
                                false);
    y = height*32/100;

    drawReplayMenuLine(_("[%s/%s] to change rate", getKeyBinding(PA_BRAKE),
                                getKeyBinding(PA_ACCEL)), y, x, false);
    y = height*36/100;

    drawReplayMenuLine(_("Rate is currently x%s",
                                StringUtils::toWString(rc->getRate())), y, x, false);
    y = height*44/100;

    drawReplayMenuLine(_("Time: %s / %s",
                                core::stringw (StringUtils::timeToString(World::getWorld()->getTime()).c_str()),
                                core::stringw (StringUtils::timeToString(rc->getDuration()).c_str())),
                                y, x, false);
    font->setBlackBorder(false);
}   // drawReplayGUI