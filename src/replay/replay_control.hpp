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

#ifndef HEADER_REPLAY_CONTROL_HPP
#define HEADER_REPLAY_CONTROL_HPP

#include <cstddef>

/** Owns the replay playback clock. This is mode-agnostic, so if you
 *  let its values reach the world state, they must be guarded by a
 *  check to see if watch replay mode is active. */
class ReplayControl
{
private:
    /** True if replay control is enabled. */
    bool   m_control_enabled;

    /** True if replay playback is playing, false if paused. */
    bool   m_is_playing;

    /** True if the direction of time is backwards */
    bool   m_is_rewinding;

    /** The rate of playback as a multiplier. */
    double m_rate;

    /** The duration of the replay, -1 until the duration is known. */
    double m_duration;

    static ReplayControl   *m_replay_control;

public:
    ReplayControl()
    {
        m_control_enabled =  false;
        m_is_playing      =  false;
        m_is_rewinding    =  false;
        m_rate            =  1.0;
        m_duration        = -1.0;
    }
    // ------------------------------------------------------------------------
    void    reset();
    // ------------------------------------------------------------------------
    bool    isControlEnabled() const { return m_control_enabled; }
    // ------------------------------------------------------------------------
    bool    isPlaying()        const { return m_is_playing; }
    // ------------------------------------------------------------------------
    bool    isRewinding()      const { return m_is_rewinding; }
    // ------------------------------------------------------------------------
    double  getRate()          const { return m_rate; }
    // ------------------------------------------------------------------------
    double  getDuration()      const { return m_duration; }
    // ------------------------------------------------------------------------
    void    setPlaying(bool playing)                { m_is_playing = playing; }
    // ------------------------------------------------------------------------
    void    setRewinding(bool rewinding)        { m_is_rewinding = rewinding; }
    // ------------------------------------------------------------------------
    void    setDuration(double duration)             { m_duration = duration; }
    // ------------------------------------------------------------------------
    void    setRate(double rate)                             { m_rate = rate; }
    // ------------------------------------------------------------------------
    /** Creates a new instance of the replay controller. */
    static void           create()  { m_replay_control = new ReplayControl(); }
    // ------------------------------------------------------------------------
    /** Returns the instance of the replay controller. */
    static ReplayControl *get()                    { return m_replay_control; }
    // ------------------------------------------------------------------------
    /** Deletes the instance of the replay controller. */
    static void          destroy()
                          { delete m_replay_control; m_replay_control = NULL; }
};
#endif
