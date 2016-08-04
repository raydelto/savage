/*! \file L5GameLayer.h
    \author <denisacostaq\@gmail.com>
    \date Fri Feb 14 00:08:48 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/L5GameLayer.h

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

#ifndef L5GAMELAYER_H
#define L5GAMELAYER_H
#include "GameLayer.h"
class L5GameLayer : public GameLayer
{
public:
    ~L5GameLayer();
    //disable copy and move
//    L5GameLayer(const L5GameLayer&) = delete;
//    L5GameLayer& operator=(const L5GameLayer&) = delete;
//    L5GameLayer(const L5GameLayer&&) = delete;
//    L5GameLayer& operator=(const L5GameLayer&&) = delete;

    static CCScene* scene(const PlayerKind &selectedPlayer);
    static L5GameLayer* create(const PlayerKind &selectedPlayer);
    virtual bool init();

protected:
    virtual void update (float dt);

private:
    L5GameLayer();

    virtual void initGame();

    void setSelectedPlayer(const PlayerKind &selectedPlayer);

    PlayerKind m_selectedPlayer;
};

#endif // L5GAMELAYER_H
