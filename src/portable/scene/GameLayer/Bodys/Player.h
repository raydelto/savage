/*! \file Player.h
    \author <denisacostaq\@gmail.com>
    \date Sat Feb  8 00:48:00 CST 2014

    \brief This file become from: TODO: src/portable/scene/GameLayer/Bodys/Player.h

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

#ifndef PLAYER_H
#define PLAYER_H

#include "scene/GameLayer/Bodys/Car.h"
#include "GlobalColaboration.h"

class Player : public Car
{
public:
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(const Player&&) = delete;
    Player& operator=(const Player&&) = delete;
    ~Player();

    static Player* create(const PlayerKind &playerKin);    

    virtual bool init() override;

    virtual void setFootpath(const Footpath& footpath);

    void acelerate();

    void crash(Car *car);

    void update();

private:
    Player(const PlayerKind &playerKin);

    void moveTo(const CCPoint& pos);
    void moveToX(const float &destineX);
    void moveToY(const float &destineY);
    void moveToYandReturn(const float &destineY);

    void moveDone();

    typedef struct
    {
        float velocityMoveToLaterals;
        float velocityAdvance;
    }Maniobrability;

    Maniobrability m_maniobrability;
    PlayerKind m_playerKin;

    float m_bottonPosition;

};

#endif // PLAYER_H
