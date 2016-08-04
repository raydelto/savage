/*! \file Body.h
    \author <denisacostaq\@gmail.com>
    \date Sat Feb  8 00:43:40 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/Bodys/Body.h

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

#ifndef BODY_H
#define BODY_H

#include "cocos2d.h"
USING_NS_CC;

#include "GlobalColaboration.h"

class Body : public CCSprite
{
  public:
//    Body(const Body&) = delete;
//    Body& operator=(const Body&) = delete;
//    Body(const Body&&) = delete;
//    Body& operator=(const Body&&) = delete;

    virtual ~Body();
    const float getVelocity() const;
    void setVelocity(const float vel);

    enum Kind{kTree, kCar, kGomas, kAceite, kBasurero};
    void setKind(const Kind kind);
    const Kind getKind() const;

    const bool& isActive() const;
    void setActive(const bool &active);

    const CCRect getBaseForCollition();

    enum Footpath {kRigth, kCenter, kLeft};
    const int& getFootpath() const;
    virtual void setFootpath(const int& footpath);

    virtual bool init();

protected:
    Body();
    float m_velocity;
    Kind m_kind;
    bool m_active;
    int m_footpath;
    std::vector<CCPoint> m_footpathPoints;
    GlobalColaboration *m_gc;
};

#endif // BODY_H
