/*! \file Obstacle.cpp
    \author <denisacostaq\@gmail.com>
    \date Sat Feb  7 25:43:40 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/Bodys/Obstacle.cpp

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

#include "Obstacle.h"

/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/
Obstacle::Obstacle()
{
}

Obstacle::~Obstacle()
{
}

Obstacle* Obstacle::create(const char *fileName)
{
    Obstacle *pRet = new Obstacle();
    if (pRet && pRet->initWithFile(fileName) && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete (pRet);
        pRet = NULL;
        return NULL;
    }
}


void Obstacle::crash(Player* collitioner)
{
    if (this->getKind() == Body::kAceite)
    {
        collitioner->resbala();
        return;
    }

    CCMoveBy *mb = NULL;
    if (m_gc->getRandomIntegerInRange(0, 2))//rigth || left
    {
        mb = CCMoveBy::create(
                .3f,
                CCPoint(
                    .003f * collitioner->getVelocity() *
                        collitioner->getContentSize().width * .5f,
                    .003f * collitioner->getVelocity() *
                        collitioner->getContentSize().height));

    }
    else
    {
        mb = CCMoveBy::create(
                .3f,
                CCPoint(
                    -.003f * collitioner->getVelocity() *
                        collitioner->getContentSize().width * .5f,
                    .003f * collitioner->getVelocity() *
                        collitioner->getContentSize().height));
    }
    this->runAction(CCSequence::createWithTwoActions(mb, mb->reverse()));

}

void Obstacle::crash(Car* collitioner)
{
    if (this->getKind() == Body::kAceite)
    {
        collitioner->resbala();
        return;
    }

    CCMoveBy *mb = NULL;
    if (m_gc->getRandomIntegerInRange(0, 2))//rigth || left
    {
        mb = CCMoveBy::create(
                1.7f,
                CCPoint(
                    .008f * collitioner->getVelocity() *
                        collitioner->getContentSize().width * .5f,
                    -.008f * collitioner->getVelocity() *
                        collitioner->getContentSize().height));
    }
    else
    {
        mb = CCMoveBy::create(
                1.7f,
                CCPoint(
                    .008f * collitioner->getVelocity() *
                        collitioner->getContentSize().width * .5f,
                    -.008f * collitioner->getVelocity() *
                        collitioner->getContentSize().height));
    }
    this->runAction(CCSequence::createWithTwoActions(mb, mb->reverse()));

}

