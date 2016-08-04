/*! \file Car.cpp
    \author <denisacostaq\@gmail.com>
    \date Sat Feb  8 00:46:14 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/Bodys/Car.cpp

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

#include "Car.h"

/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/
Car::Car() 
{
}

Car::~Car()
{
}

Car* Car::create(const char *fileName)
{
    Car *pRet = new Car();
    if (pRet && pRet->initWithFile(fileName) && pRet->init())
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



void Car::crash(bool toLeft)
{
    //FIXME: fadeback?? CCRotateBy *rb = CCRotateBy::create(.4f, 3.0f);
//    this->runAction(
//                CCRepeat::create(
//                    CCSequence::createWithTwoActions(rb, rb->reverse()),4));
    if (toLeft)
    {
        this->runAction(
                    CCMoveBy::create(1.0f,
                        CCPoint{
                            -this->getContentSize().width * 2.0f,
                            0.0f}));
    }
    else
    {
        this->runAction(
                    CCMoveBy::create(1.0f,
                        CCPoint{
                            this->getContentSize().width * 2.0f,
                            0.0f}));
    }
}

void Car::resbala()
{
    if (m_gc->getRandomIntegerInRange(0, 2))//left || rigth
    {
        this->runAction(
                    CCMoveBy::create(
                        3.0f,
                        CCPoint{this->getContentSize().width*.5f,
                              -this->getContentSize().height*.5f}));
    }
    else
    {
        this->runAction(
                    CCMoveBy::create(
                        3.0f,
                        CCPoint{-this->getContentSize().width*.5f,
                              -this->getContentSize().height*.5f}));
    }

}



