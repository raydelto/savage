/*! \file Collition.h
    \author <denisacostaq\@gmail.com>
    \date Sun Feb  9 20:47:03 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/Helpers/Collition.h

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

#ifndef COLLITION_H
#define COLLITION_H
#include "cocos2d.h"
class Collition
{
public:
//    Collition() = delete;
//    Collition(const Collition&) = delete;
//    Collition& operator=(const Collition&) = delete;
//    Collition(const Collition&&) = delete;
//    Collition& operator=(const Collition&&) = delete;

    Collition(cocos2d::CCObject *body1, cocos2d::CCObject *body2);

     cocos2d::CCObject *getBody1() const;
     cocos2d::CCObject *getBody2() const;

     bool operator< ( const Collition& rigth) const;
     bool operator> ( const Collition& rigth) const;

private:
    cocos2d::CCObject *m_body1;
    cocos2d::CCObject *m_body2;

};


#endif // COLLITION_H
