//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2010-2013 SuperTuxKart-Team
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

#ifndef GAME_SLOT_HPP
#define GAME_SLOT_HPP

#include "race/race_manager.hpp"

#include <irrString.h>
using namespace irr;

#include <string>
#include <map>
#include <vector>


class Challenge;
class ChallengeData;
class UTFWriter;
class XMLNode;

const int CHALLENGE_POINTS[] = { 8, 9, 10 };

/**
 * \ingroup challenges
 * This class contains the progression through challenges for one game slot
 */

class GameSlot
{
    /** Profile names can change, so rather than try to make sure all renames
     *  are done everywhere, assign a unique ID to each profiler.
     *  Will save much headaches.
     */
    unsigned int m_player_unique_id;

    /** Contains whether each feature of the challenge is locked or unlocked */
    std::map<std::string, bool>   m_locked_features;

    /** Recently unlocked features (they are waiting here
      * until they are shown to the user) */
    std::vector<const ChallengeData*> m_unlocked_features;

    std::map<std::string, Challenge*> m_challenges_state;

    /** A pointer to the current challenge, or NULL
     *  if no challenge is active. */
    const Challenge *m_current_challenge;

    friend class UnlockManager;

    int m_points;

    /** Set to false after the initial stuff (intro, select kart, etc.) */
    bool m_first_time;

    int m_easy_challenges;
    int m_medium_challenges;
    int m_hard_challenges;

public:

     GameSlot(const XMLNode *node=NULL);
    ~GameSlot();

    void computeActive();
    bool       isLocked          (const std::string& feature);
    void       lockFeature       (Challenge *challenge);
    void       unlockFeature     (Challenge* c, RaceManager::Difficulty d,
                                  bool do_save=true);
    void       raceFinished      ();
    void       grandPrixFinished ();
    void       save              (UTFWriter &out);
    void       setCurrentChallenge(const std::string &challenge_id);

    // ------------------------------------------------------------------------
    /** Returns the list of recently unlocked features (e.g. call at the end
     *  of a race to know if any features were unlocked) */
    const std::vector<const ChallengeData*>
        getRecentlyCompletedChallenges() {return m_unlocked_features;}
    // ------------------------------------------------------------------------
    /** Clear the list of recently unlocked challenges */
    void       clearUnlocked     () {m_unlocked_features.clear(); }
    // ------------------------------------------------------------------------
    /** Returns the number of points accumulated. */
    int        getPoints          () const { return m_points; }
    // ------------------------------------------------------------------------
    /** Returns the number of fulfilled challenges at easy level. */
    int        getNumEasyTrophies  () const { return m_easy_challenges;   }
    // ------------------------------------------------------------------------
    /* Returns the number of fulfilled challenges at medium level. */
    int        getNumMediumTrophies() const { return m_medium_challenges; }
    // ------------------------------------------------------------------------
    /** Returns the number of fulfilled challenges at har level. */
    int        getNumHardTrophies  () const { return m_hard_challenges;   }
    // ------------------------------------------------------------------------
    /** Sets if this is the first time the intro is shown. */
    void       setFirstTime(bool ft) { m_first_time = ft;   }
    // ------------------------------------------------------------------------
    /** Returns if this is the first time the intro is shown. */
    bool       isFirstTime() const   { return m_first_time; }
    // ------------------------------------------------------------------------
    const Challenge *getCurrentChallenge() const { return m_current_challenge; }
    // ------------------------------------------------------------------------
    /** Returns a challenge given the challenge id.
     */
    const Challenge* getChallenge(const std::string& id) const
    {
        std::map<std::string, Challenge*>::const_iterator it =
            m_challenges_state.find(id);
        assert(it!=m_challenges_state.end());
        return it->second;
    }   // getChallenge
};   // GameSlot

#endif
