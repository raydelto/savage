/*! \file PlayerSelection.h
    \author <denisacostaq\@gmail.com>
    \date Tue Feb 11 03:16:27 CST 2014

    \brief This file become from: src/portable/scene/MainMenu/PlayerSelection.h

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

#ifndef PLAYERSELECTION_H
#define PLAYERSELECTION_H

#include "cocos2d.h"
USING_NS_CC;

#include "AppMacros.h"
#include "scene/GameLayer/L1GameLayer.h"
#include "scene/GameLayer/L2GameLayer.h"
#include "scene/GameLayer/L3GameLayer.h"
#include "scene/GameLayer/L4GameLayer.h"
#include "scene/GameLayer/L5GameLayer.h"
class PlayerSelection : public CCLayer
{
public:
    //NOTE: disable copy and move
//    PlayerSelection(const PlayerSelection&) = delete;
//    PlayerSelection& operator= (const PlayerSelection&) = delete;
//    PlayerSelection(const PlayerSelection&&) = delete;
//    PlayerSelection& operator= (PlayerSelection&&) = delete;

    ~PlayerSelection();
    static CCScene* scene(int levelSelected);
    CREATE_FUNC(PlayerSelection)

    virtual bool init();

private:
    PlayerSelection();

    void initMembers();
    void initBackground();
    void initMenu();

    void menuPlayCallback(CCObject *pSender);
    void menuBackCallback();

    CCSize m_visibleSize;
    static int m_levelSelected;
};

#endif // PLAYERSELECTION_H
