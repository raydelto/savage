/*! \file CarWithPerspective.cpp
    \author <denisacostaq\@gmail.com>
    \date Sat Feb  8 01:46:14 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/Bodys/CarWithPerspective.cpp

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

#include "CarWithPerspective.h"

/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/
CarWithPerspective::CarWithPerspective()
{
}

CarWithPerspective::~CarWithPerspective()
{
}

CarWithPerspective* CarWithPerspective::create(const char* fileName)
{
    CarWithPerspective *pRet = new CarWithPerspective();
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


/******************************************************************************/
/*                                    INIT                                    */
/******************************************************************************/
bool CarWithPerspective::init()
{
    if (!Car::init())
    {
        return false;
    }

    CCArray *perpective = CCArray::createWithCapacity(2);
    perpective->addObject(
                CCSpriteFrame::create("GamePlay/Guagua-deracha.png",
                                    CCRect{0.0f,
                                         0.0f,
                                         this->getContentSize().width,
                                         this->getContentSize().height}));
    perpective->addObject(
                CCSpriteFrame::create("GamePlay/Guagua-Izquierda.png",
                                    CCRect{0.0f,
                                         0.0f,
                                         this->getContentSize().width,
                                         this->getContentSize().height}));
    CCAnimation* perspAnim = CCAnimation::createWithSpriteFrames(perpective);
    CCAnimationCache::sharedAnimationCache()->addAnimation(perspAnim, "perspAnim");
    CC_SAFE_RELEASE_NULL(perpective);

    return true;
}



void CarWithPerspective::setFootpath(const Footpath& footpath)
{
    Car::setFootpath(footpath);
    if (footpath == Footpath::kLeft)
    {
        this->setDisplayFrameWithAnimationName("perspAnim", 0);
    }
    else if (footpath == Footpath::kRigth)
    {
        this->setDisplayFrameWithAnimationName("perspAnim", 1);
    }
}
