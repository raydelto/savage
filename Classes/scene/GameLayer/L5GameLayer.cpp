/*! \file L5GameLayer.h
    \author <denisacostaq\@gmail.com>
    \date Fri Feb 14 00:08:48 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/L5GameLayer.h

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

#include "L5GameLayer.h"

/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/
L5GameLayer::L5GameLayer()
 : m_selectedPlayer (kPlayer_1)
{
}

L5GameLayer::~L5GameLayer()
{
    delete(m_terrain);
}

CCScene* L5GameLayer::scene(const PlayerKind &selectedPlayer)
{
    CCScene *scene = CCScene::create();
    GameLayer *layer = L5GameLayer::create(selectedPlayer);
    scene->addChild(layer);
    return scene;
}

L5GameLayer* L5GameLayer::create(const PlayerKind &selectedPlayer)
{
    L5GameLayer *pRet = new L5GameLayer();
    if (pRet)
    {
        pRet->setSelectedPlayer(selectedPlayer);
        if (pRet->init())
        {
            pRet->setSelectedPlayer(selectedPlayer);
            return pRet;
        }
        else
        {
            delete (pRet);
            pRet = NULL;
            return NULL;
        }
    }
    else
    {
        delete (pRet);
        pRet = NULL;
        return NULL;
    }
}


/******************************************************************************/
/*                                    INIT                                    */
/******************************************************************************/
bool L5GameLayer::init()
{
    //WARNING: esto es necesario establecerlo antede llamat el init de GameLayer
    //ya que este se refiere a el como si ya existiera, de hecho ya deberia exis
    m_terrain = Terrain::create(m_selectedPlayer, Terrain::kLevel_5);
    if(!GameLayer::init())
    {
        return false;
    }

    return true;
}

void L5GameLayer::setSelectedPlayer(const PlayerKind &selectedPlayer)
{
    m_selectedPlayer = selectedPlayer;
}


void L5GameLayer::initGame()
{
    m_currentLevel = 5;
    m_terrain->changeFootpathTo(Car::kCenter);
    m_timmer = m_cTimerValue;
    m_timmerLabel->resumeSchedulerAndActions();
    m_gameStatus = Terrain::kPlaying;

    this->schedule(schedule_selector(L5GameLayer::putObstacle), 3.f);
    this->schedule(schedule_selector(L5GameLayer::putCar), 2.5f);
    this->schedule(schedule_selector(L5GameLayer::putTree), .5f);
    this->schedule(schedule_selector(L5GameLayer::update));
}

void L5GameLayer::update(float dt)
{
    if (m_terrain->getVelocity() < 100)
    {
        m_timmer = m_cTimerValue;
    }

    if (m_timmer < 30)
    {
        this->schedule(schedule_selector(L5GameLayer::putCar), 4.5f);
        this->schedule(schedule_selector(L5GameLayer::putObstacle), 4.0f);
    }
    else if (m_timmer < 15)
    {
        this->schedule(schedule_selector(L5GameLayer::putObstacle), 1.0f);
    }
    GameLayer::update(dt);
}
