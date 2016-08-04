/*! \file Collition.cpp
    \author <denisacostaq\@gmail.com>
    \date Sun Feb  9 20:47:03 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/Helpers/Collition.cpp

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


#include "Collition.h"

/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/
Collition::Collition(cocos2d::CCObject *body1, cocos2d::CCObject *body2)
    : m_body1 {body1}
    , m_body2 {body2}
{
    if(m_body1->m_uID > m_body2->m_uID)
    {
        std::swap(m_body1, m_body2);
    }
}

bool Collition::operator<(const Collition& rigth) const
{
    if(m_body1->m_uID < rigth.m_body1->m_uID)
    {
        return true;
    }
    else if(m_body1->m_uID > rigth.m_body1->m_uID)
    {
        return false;
    }
    else
    {
        return m_body2->m_uID < rigth.m_body2->m_uID;
    }
}

bool Collition::operator>(const Collition& rigth) const
{
    if(m_body1->m_uID > rigth.m_body1->m_uID)
    {
        return true;
    }
    else if(m_body1->m_uID < rigth.m_body1->m_uID)
    {
        return false;
    }
    else
    {
        return m_body2->m_uID > rigth.m_body2->m_uID;
    }
}



cocos2d::CCObject *Collition::getBody1() const
{
    return m_body1;
}

cocos2d::CCObject *Collition::getBody2() const
{
    return m_body2;
}
