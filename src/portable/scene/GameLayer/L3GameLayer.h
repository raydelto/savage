/*! \file L3GameLayer.h
    \author <denisacostaq\@gmail.com>
    \date Fri Feb 14 00:05:29 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/L3GameLayer.h

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

#ifndef L3GAMELAYER_H
#define L3GAMELAYER_H
#include "GameLayer.h"
class L3GameLayer : public GameLayer
{
public:
    ~L3GameLayer();
    //disable copy and move
    L3GameLayer(const L3GameLayer&) = delete;
    L3GameLayer& operator=(const L3GameLayer&) = delete;
    L3GameLayer(const L3GameLayer&&) = delete;
    L3GameLayer& operator=(const L3GameLayer&&) = delete;

    static CCScene* scene(const PlayerKind &selectedPlayer);
    static L3GameLayer* create(const PlayerKind &selectedPlayer);
    virtual bool init() override;

protected:
    virtual void update (float dt) override;

private:
    L3GameLayer();

    virtual void initGame() override;

    void setSelectedPlayer(const PlayerKind &selectedPlayer);

    PlayerKind m_selectedPlayer;
};

#endif // L3GAMELAYER_H