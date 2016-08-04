/*! \file CCMenuLayer.h
    \author <denisacostaq\@gmail.com>
    \date Fri Feb  7 20:10:41 CST 2014

    \brief This file become from: src/portable/scene/MainMenu/MenuLayer.h

    \attention <h1><center>&copy; COPYRIGHT
    GNU GENERAL PUBLIC LICENSE Version 2, June 1991</center></h1>

    \copyright

    <h3>This file is part of <a href="http://www.savage_race.com"><strong>SavageRace</strong></a> program, a short 2D game.</h3>
    Copyright (C) 2013  denisacostaq\@gmail.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef CCMenuLAYER_H
#define CCMenuLAYER_H

#include "GlobalColaboration.h"
#include "SimpleAudioEngine.h"
#include "CreditsLayer.h"
#include "LevelSelection.h"
#include "scene/GameLayer/L1GameLayer.h"

USING_NS_CC;

namespace MainMenu
{
class MenuLayer : public CCLayer
{
public:
//    MenuLayer(const MenuLayer&) = delete;
//    MenuLayer& operator=(const MenuLayer&) = delete;
//    MenuLayer(const MenuLayer&&) = delete;
//    MenuLayer& operator=(const MenuLayer&&) = delete;

    ~MenuLayer ();

    static CCScene* scene();
    CREATE_FUNC(MenuLayer)
    virtual bool init ();

private:
    MenuLayer();

    void initMembers();
    void initBackground();
    void initSounds();
    void initMenu();

    void menuPlayCallback();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    void CCMenuInviteBBFriendsCallback();
#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    void menuCreditsCallback();
    void menuAudioTogleCallback();
    void menuExitCallback();

    CCSize m_visibleSize;
    CCPoint m_visibleOrigin;
    bool m_playingAudio;
};
}
#endif //MENULAYER_H
