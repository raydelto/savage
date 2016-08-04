/*! \file L3GameLayer.cpp
    \author <denisacostaq\@gmail.com>
    \date Fri Feb 14 00:05:29 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/L3GameLayer.cpp

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
#include "L3GameLayer.h"

/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/
L3GameLayer::L3GameLayer()
 : m_selectedPlayer {PlayerKind::kPlayer_1}
{
}

L3GameLayer::~L3GameLayer()
{
    delete(m_terrain);
}

CCScene* L3GameLayer::scene(const PlayerKind &selectedPlayer)
{
    CCScene *scene = CCScene::create();
    GameLayer *layer = L3GameLayer::create(selectedPlayer);
    scene->addChild(layer);
    return scene;
}

L3GameLayer* L3GameLayer::create(const PlayerKind &selectedPlayer)
{
    L3GameLayer *pRet = new L3GameLayer();
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
            pRet = nullptr;
            return nullptr;
        }
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
bool L3GameLayer::init()
{
    //WARNING: esto es necesario establecerlo antede llamat el init de GameLayer
    //ya que este se refiere a el como si ya existiera, de hecho ya deberia exis
    m_terrain = Terrain::create(m_selectedPlayer, Terrain::Level::kLevel_1);
    if(!GameLayer::init())
    {
        return false;
    }

    return true;
}

void L3GameLayer::setSelectedPlayer(const PlayerKind &selectedPlayer)
{
    m_selectedPlayer = selectedPlayer;
}


void L3GameLayer::initGame()
{
    m_currentLevel = 3;
    m_terrain->changeFootpathTo(Car::Footpath::kCenter);
    m_timmer = m_cTimerValue;
    m_timmerLabel->resumeSchedulerAndActions();
    m_gameStatus = Terrain::GameStatus::kPlaying;

    this->schedule(schedule_selector(L3GameLayer::putObstacle), 3.f);
    this->schedule(schedule_selector(L3GameLayer::putCar), 3.5f);
    this->schedule(schedule_selector(L3GameLayer::putTree), 1.5f);
    this->schedule(schedule_selector(L3GameLayer::update));
}

void L3GameLayer::update(float dt)
{
    if (m_terrain->getVelocity() < 100)
    {
        m_timmer = m_cTimerValue;
    }
    GameLayer::update(dt);
}
