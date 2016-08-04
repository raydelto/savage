/*! \file Player.cpp
    \author <denisacostaq\@gmail.com>
    \date Sat Feb  8 00:48:00 CST 2014

    \brief This file become from: TODO: src/portable/scene/GameLayer/Bodys/Player.cpp

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

#include "Player.h"

/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/
Player::Player(const PlayerKind &playerKin)
    : m_playerKin (playerKin)
    , m_bottonPosition (0.0f)
{
}

Player::~Player()
{
}

Player* Player::create(const PlayerKind &playerKin)
{
    char filename[40] = {0};
    switch (playerKin)
    {
    case kPlayer_1:
        sprintf (filename, "GamePlay/Auto-Azul.png");
        break;
    case kPlayer_2:
        sprintf (filename, "GamePlay/Auto-Amarillo.png");
        break;
    case kPlayer_3:
        sprintf (filename, "GamePlay/Auto-Rojo.png");
        break;
    default:
        break;
    }
    Player *pRet = new Player(playerKin);
    if (pRet && pRet->initWithFile(filename) && pRet->init())
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



void Player::setFootpath(const int& footpath)
{
    m_footpath = footpath;
    switch (m_footpath)
    {
        case Car::kLeft:
            this->moveToX(m_footpathPoints[0].x);
            break;
        case Car::kCenter:
            this->moveToX(m_footpathPoints[1].x);
            break;
        case Car::kRigth:
            this->moveToX(m_footpathPoints[2].x);
            break;
        default:
            break;
    }
}

void Player::acelerate()
{
    this->moveToYandReturn(this->getPositionY() +
                           this->getContentSize().height*.5f);
}

void Player::moveTo(const CCPoint& pos)
{
    if (this->getPositionX() != pos.x)
    {
        this->moveToX(pos.x);
    }

    if (this->getPositionY() != pos.y)
    {
        this->moveToYandReturn(pos.y);
    }
}

void Player::moveToX(const float &destineX)
{
    const float intervalToLaterals = m_gc->getInterval(
                this->getPositionX(),
                destineX,
                m_maniobrability.velocityMoveToLaterals);

    CCSequence *rt = NULL;
    if (this->getPositionX() < destineX)
    {
        rt = CCSequence::createWithTwoActions(
                    CCRotateTo::create(intervalToLaterals * .58f,
                                     intervalToLaterals * 18.0f),
                    CCRotateTo::create(intervalToLaterals * .38f,
                                     0.0f));
    }
    else
    {
        rt = CCSequence::createWithTwoActions(
                    CCRotateTo::create(intervalToLaterals * .58f,
                                     -intervalToLaterals * 18.0f),
                    CCRotateTo::create(intervalToLaterals * .38f,
                                     0.0f));
    }

    CCMoveTo *vt = CCMoveTo::create(intervalToLaterals,
                                CCPoint(destineX, this->getPositionY()));

    CCSequence *secureMove = CCSequence::createWithTwoActions(
                vt, CCCallFuncN::create(this, callfuncN_selector(Player::moveDone)));
    this->runAction(secureMove);
    this->runAction(rt);
}

void Player::moveToYandReturn(const float &destineY)
{
    const float intervalToVertical = m_gc->getInterval(
                this->getPositionY(),
                destineY,
                m_maniobrability.velocityAdvance);

    CCSequence *vt = CCSequence::createWithTwoActions(
                        CCMoveTo::create(intervalToVertical,
                            CCPoint(this->getPositionX(), destineY)),
                        CCMoveTo::create(intervalToVertical * 2,
                            CCPoint(this->getPositionX(), this->getPositionY())));

    CCSequence *secureMove = CCSequence::createWithTwoActions(
                vt, CCCallFuncN::create(this, callfuncN_selector(Player::moveDone)));
    this->runAction(secureMove);
}

void Player::moveToY(const float &destineY)
{
    const float intervalToMove = m_gc->getInterval(
                this->getPositionY(),
                destineY,
                m_maniobrability.velocityAdvance);
    this->runAction(CCMoveTo::create(intervalToMove,
                                   CCPoint(this->getPositionX(), destineY)));
}

void Player::moveDone()
{
    this->stopAllActions();

    if (this->getPositionY() >
            m_bottonPosition + this->getContentSize().height*.2f ||
        this->getPositionY() <
            m_bottonPosition - this->getContentSize().height*.2f)
    {
        this->moveToY(m_bottonPosition);
    }

    switch (m_footpath)
    {
        case kLeft:
            if (this->getPositionX() >
                    m_footpathPoints[0].x + this->getContentSize().width*.2f ||
                this->getPositionX() <
                    m_footpathPoints[0].x - this->getContentSize().width*.2f)
            {
                this->moveToX(m_footpathPoints[0].x);
            }

            break;
        case kCenter:
            if (this->getPositionX() >
                    m_footpathPoints[1].x + this->getContentSize().width*.2f ||
                this->getPositionX() <
                    m_footpathPoints[1].x - this->getContentSize().width*.2f)
            {
                this->moveToX(m_footpathPoints[1].x);
            }
            break;
        case kRigth:
            if (this->getPositionX() >
                    m_footpathPoints[2].x + this->getContentSize().width*.2f ||
                this->getPositionX() <
                    m_footpathPoints[2].x - this->getContentSize().width*.2f)
            {
                this->moveToX(m_footpathPoints[2].x);
            }
            break;
        default:
            break;
    }
}

bool Player::init()
{
    if (!Car::init())
    {
        return false;
    }

    switch (m_playerKin)
    {
    case kPlayer_1:
        m_maniobrability.velocityMoveToLaterals = 150.0f;
        m_maniobrability.velocityAdvance = 40.0f;
        break;
    case kPlayer_2:
        m_maniobrability.velocityMoveToLaterals = 200.0f;
        m_maniobrability.velocityAdvance = 70.0f;
        break;
    case kPlayer_3:
        m_maniobrability.velocityMoveToLaterals = 300.0f;
        m_maniobrability.velocityAdvance = 100.0f;
        break;
    default:
        break;
    }

    m_bottonPosition = this->getContentSize().height * .6f;
    return true;
}

void Player::crash(Car *car)
{
    bool toleft = car->getPositionX() < this->getPositionX();
    CCRotateBy *descontrol = CCRotateBy::create(.2f, 10.f);
    this->runAction(CCRepeat::create(CCSequence::createWithTwoActions(descontrol, descontrol->reverse()), 3));
    car->crash(toleft);
    Car::crash(!toleft);
}

void Player::update()
{
    return;
    if (this->getPositionX() < m_footpathPoints[0].x)
    {
        this->setFootpath(Car::kLeft);
    }
    else if (this->getPositionX() > m_footpathPoints[3].x)
    {
        this->setFootpath(Car::kRigth);
    }
}
