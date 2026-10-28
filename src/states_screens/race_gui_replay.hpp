//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2026 Gustavo Barreira
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

#ifndef HEADER_RACE_GUI_GHOST_HPP
#define HEADER_RACE_GUI_GHOST_HPP

#include <map>
#include <string>
#include <vector>

#include <irrString.h>
using namespace irr;

#include "states_screens/race_gui_base.hpp"

class Kart;
class InputMap;
class Material;
class RaceSetup;

/**
 * \brief Handles the in-race GUI (messages, mini-map, rankings, timer, etc...)
 * \ingroup states_screens
 */
class RaceGUIReplay : public RaceGUIBase
{
private:
    /** Height of the digit font. */
    int m_font_height;

    /** Icon textures (stored as variables to not look up
        their location on every frame) */
    irr::video::ITexture *m_red_team;

    /** Display items that are shown once only (for all karts). */
    void drawReplayGUI();

    /** Helper function for drawing the replay control menu */
    void drawReplayMenuLine(const core::stringw &text, int y, int x, bool hcenter);

public:
    RaceGUIReplay();
    virtual void init();
    virtual void reset();
    virtual void initSize();

    /** Returns the size of the texture on which to render the minimap to. */
    virtual const core::dimension2du getMiniMapSize() const
    {
        return core::dimension2du(0, 0);
    }
}; // RaceGUIReplay

#endif
