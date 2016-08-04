/*! \file Tree.h
    \author <denisacostaq\@gmail.com>
    \date Sun Feb  9 05:46:49 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/Bodys/Tree.h

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

#ifndef TREE_H
#define TREE_H
#include "Body.h"

class Tree : public Body
{
public:

//    Tree(const Tree&) = delete;
//    Tree&  operator=(const Tree&) = delete;
//    Tree(const Tree&&) = delete;
//    Tree& operator=(const Tree&&) = delete;

    static Tree* create(const char* filename);
    ~Tree();

    void setToLeft();
    void setToRigth();

    void setRigth(const float& rigth);
    void setLeft(const float& left);

private:
    Tree();
    float m_left;
    float m_rigth;
};

#endif // TREE_H
