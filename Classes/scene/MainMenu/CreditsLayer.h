/*! \file CreditsLayer.h
    \author <denisacostaq\@gmail.com>
    \date Tue Feb 11 05:19:08 CST 2014

    \brief This file become from: src/portable/scene/MainMenu/CreditsLayer.h

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

#ifndef CREDITSLAYER_H
#define CREDITSLAYER_H

#include "AppMacros.h"
#include "scene/GameLayer/Helpers/Terrain.h"

#include "label_nodes/CCLabelTTF.h"
USING_NS_CC;

class CreditsLayer : public CCLayer
{
public:

//    CreditsLayer(const CreditsLayer&) = delete;
//    CreditsLayer& operator=(const CreditsLayer&) = delete;
//    CreditsLayer(const CreditsLayer&&) = delete;
//    CreditsLayer& operator=(const CreditsLayer&&) = delete;

    ~CreditsLayer();

    static CCScene* scene();
    CREATE_FUNC(CreditsLayer)
    virtual bool init();
private:
    CreditsLayer();

    void initMembers();
    void initBackground();
    void initCredentials();
    void initMenu();

    void updatePutCar(float dt);
    void updatePutTree(float dt);

    void menuBackCallback();

    CCSize m_visibleSize;
    Terrain *m_terrain;
};

#endif // CREDITSLAYER_H
