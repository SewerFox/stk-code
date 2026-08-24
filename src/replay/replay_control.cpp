//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2026 Markuss Milais
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

#include "replay/replay_control.hpp"
#include <cstddef>

ReplayControl *ReplayControl::m_replay_control = NULL;

void ReplayControl::reset()
{
    m_control_enabled =  true;
    m_is_playing      =  true;
    m_is_rewinding    =  false;
    m_rate            =  1.0;
    m_duration        = -1.0;
}
