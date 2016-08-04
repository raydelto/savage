/*! \file Body.cpp
    \author <denisacostaq\@gmail.com>
    \date Sat Feb  8 00:43:40 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/Bodys/Body.cpp

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

#include "Body.h"
/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/
Body::Body()
    : m_velocity{0.f}
    , m_kind {Kind::kTree}
    , m_active {false}
    , m_footpath{Footpath::kCenter}
    , m_gc {GlobalColaboration::getInstance()}//NOTE: do not free, is a singletlon
{
}

Body::~Body()
{
}

/******************************************************************************/
/*                                    INIT                                    */
/******************************************************************************/
bool Body::init()
{
    CCSize visibleSize = CC_DIRECTOR->getVisibleSize();
    m_footpathPoints.push_back(CCPoint{visibleSize.width*.3f, 0.0f});
    m_footpathPoints.push_back(CCPoint{visibleSize.width*.5f, 0.0f});
    m_footpathPoints.push_back(CCPoint{visibleSize.width*.69f, 0.0f});
    return true;
}

const float Body::getVelocity() const
{
    return m_velocity;
}

void Body::setVelocity(const float vel)
{
    m_velocity = vel*(4/CCDirector::sharedDirector()->getContentScaleFactor());
}

const Body::Kind Body::getKind() const
{
    return m_kind;
}

void Body::setKind(const Kind kind)
{
    m_kind = kind;
}


const bool& Body::isActive() const
{
    return m_active;
}

void Body::setActive(const bool& active)
{
    m_active = true;
}

const CCRect Body::getBaseForCollition ()
{
    return CCRect (this->getPositionX() - this->getContentSize().width/2,
                 this->getPositionY() - this->getContentSize().height/2,
                 this->getContentSize().width,
                 this->getContentSize().height);
}

const Body::Footpath& Body::getFootpath() const
{
    return m_footpath;
}

void Body::setFootpath(const Footpath& footpath)
{
    m_footpath = footpath;
    switch (m_footpath)
    {
    case Footpath::kLeft:
        this->setPositionX(m_footpathPoints[0].x);
        break;
    case Footpath::kCenter:
        this->setPositionX(m_footpathPoints[1].x);
        break;
    case Footpath::kRigth:
        this->setPositionX(m_footpathPoints[2].x);
        break;
    default:
        break;
    }
}
