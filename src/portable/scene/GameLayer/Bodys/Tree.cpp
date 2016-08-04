/*! \file Tree.cpp
    \author <denisacostaq\@gmail.com>
    \date Sun Feb  9 05:46:49 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/Bodys/Tree.cpp

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

#include "Tree.h"

/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/
Tree::Tree()
{
}

Tree::~Tree()
{
}

Tree* Tree::create(const char* filename)
{
    Tree* pRet = new Tree();
    if (pRet && pRet->initWithFile(filename))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete (pRet);
        pRet = nullptr;
        return nullptr;
    }
}

void Tree::setToLeft()
{
    this->setPositionX(m_left);
}

void Tree::setToRigth()
{
    this->setPositionX(m_rigth);
}


void Tree::setRigth(const float& rigth)
{
    m_rigth = rigth;
}

void Tree::setLeft(const float& left)
{
    m_left = left;
}
