/*! \file PlayerSelection.cpp
    \author <denisacostaq\@gmail.com>
    \date Tue Feb 11 03:16:27 CST 2014

    \brief This file become from: src/portable/scene/MainMenu/PlayerSelection.cpp

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

#include "PlayerSelection.h"

/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/
PlayerSelection::PlayerSelection()
 : m_visibleSize (CCSize(0.f, 0.f))
{
}
PlayerSelection::~PlayerSelection()
{
}

int PlayerSelection::m_levelSelected = 1;
CCScene* PlayerSelection::scene(int levelSelected)
{
    PlayerSelection::m_levelSelected = levelSelected;
    CCScene *scene = CCScene::create();
    CCLayer *layer = PlayerSelection::create();
    scene->addChild(layer);
    return scene;
}


/******************************************************************************/
/*                                    INIT                                    */
/******************************************************************************/
bool PlayerSelection::init()
{
    if (!CCLayer::init())
    {
        return true;
    }

    initMembers();
    initBackground();
    initMenu();
    return true;
}

void PlayerSelection::initMembers()
{
    m_visibleSize  = CC_DIRECTOR->getVisibleSize();
}

void PlayerSelection::initBackground()
{
    CCSprite *bg = CCSprite::create("GamePlay/Street.jpg");
    bg->setPosition(CCPoint(m_visibleSize.width*.5f,
                          m_visibleSize.height*.5f));
    this->addChild(bg, static_cast<int>(zIndex_0));
}

void PlayerSelection::initMenu()
{
    CCArray *pMenuItems = CCArray::create();
    CCMenuItemImage *pBadItem = CCMenuItemImage::create(
        "Interfaz/carro1of.png",
        "Interfaz/carro1on.png",
        this,
        menu_selector(PlayerSelection::menuPlayCallback));
    pBadItem->setPosition (CCPoint(m_visibleSize.width*.5f,
                                   m_visibleSize.height*.8f));
    pBadItem->setTag(0);
    pMenuItems->addObject(pBadItem);

    CCMenuItemImage *pMediumItem = CCMenuItemImage::create(
        "Interfaz/carro2of.png",
        "Interfaz/carro2on.png",
        "Interfaz/carro2bloqueado.png",
        this,
        menu_selector(PlayerSelection::menuPlayCallback));
    pMediumItem->setPosition (CCPoint(m_visibleSize.width*.5f,
                                  m_visibleSize.height*.5f));
    pMediumItem->setTag(1);
    pMenuItems->addObject(pMediumItem);
    if(m_levelSelected < 2) {
        pMediumItem->setEnabled(false);
    }

    CCMenuItemImage *pBestItem = CCMenuItemImage::create(
        "Interfaz/carro3of.png",
        "Interfaz/carro3on.png",
        "Interfaz/carro3bloqueado.png",
        this,
        menu_selector(PlayerSelection::menuPlayCallback));
    pBestItem->setPosition (CCPoint(m_visibleSize.width*.5f,
                                  m_visibleSize.height*.2f));
    pBestItem->setTag(2);
    pMenuItems->addObject(pBestItem);
    if(m_levelSelected < 4) {
        pBestItem->setEnabled(false);
    }

    CCMenuItemImage *pBackItem = CCMenuItemImage::create(
        "Interfaz/Flecha-of.png",
        "Interfaz/Flecha-on.png",
        this,
        menu_selector(PlayerSelection::menuBackCallback));
    pBackItem->setPosition (CCPoint(m_visibleSize.width*.5f,
                                     m_visibleSize.height*.05f));
    pMenuItems->addObject(pBackItem);

    CCMenu *pMenu = CCMenu::createWithArray (pMenuItems);
    pMenu->setPosition(ccp(0.f, 0.f));
    this->addChild(pMenu, static_cast<int>(zIndex_1));
}


/******************************************************************************/
/*                                 CALLBACKS                                  */
/******************************************************************************/
void PlayerSelection::menuPlayCallback (CCObject *pSender)
{
    PlayerKind playerKind = kPlayer_1;
    switch (static_cast<CCMenuItemImage*>(pSender)->getTag())
    {
    case 0:
        playerKind = kPlayer_1;
        break;
    case 1:
        playerKind = kPlayer_2;
        break;
    case 2:
        playerKind = kPlayer_3;
        break;
    default:
        break;
    }

    switch (m_levelSelected)
    {
    case 1:
        CC_DIRECTOR->pushScene(L1GameLayer::scene(playerKind));
        break;
    case 2:
        CC_DIRECTOR->pushScene(L2GameLayer::scene(playerKind));
        break;
    case 3:
        CC_DIRECTOR->pushScene(L3GameLayer::scene(playerKind));
        break;
    case 4:
        CC_DIRECTOR->pushScene(L4GameLayer::scene(playerKind));
        break;
    case 5:
        CC_DIRECTOR->pushScene(L5GameLayer::scene(playerKind));
        break;
    default:
        break;
    }

}

void PlayerSelection::menuBackCallback()
{
    CC_DIRECTOR->popScene();
}
