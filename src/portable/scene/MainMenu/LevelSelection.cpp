/*! \file LevelSelection.cpp
    \author <denisacostaq\@gmail.com>
    \date Tue Feb 11 04:49:38 CST 2014

    \brief This file become from: src/portable/scene/MainMenu/LevelSelection.cpp

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
#include "LevelSelection.h"

/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/
LevelSelection::LevelSelection()
    : m_visibleSize {CCSize(0.f, 0.f)}
    , m_visibleOrigin {ccp(0.f, 0.f)}
    , m_menuItems {nullptr}
{
}

LevelSelection::~LevelSelection()
{
}


CCScene* LevelSelection::scene()
{
    CCScene *scene = CCScene::create();
    CCLayer *layer = LevelSelection::create();
    scene->addChild(layer);
    return scene;
}


/******************************************************************************/
/*                                    INIT                                    */
/******************************************************************************/
void LevelSelection::onEnter()
{
    CCLayer::onEnter();
    int levels = GlobalColaboration::getInstance()->getAvaliablesLevels();
    int con = 1;
    CCObject *it = nullptr;
    CCARRAY_FOREACH(m_menuItems, it)
    {
        if(levels >= con++)
        {
            static_cast<CCMenuItemImage*>(it)->setEnabled(true);
        }
    }
}

bool LevelSelection::init()
{
    if (!CCLayer::init())
    {
        return false;
    }

    initMembers();
    initBackground();
    initMenu();

    return true;
}

void LevelSelection::initMembers()
{
    m_visibleSize = CC_DIRECTOR->getVisibleSize();
    m_visibleOrigin = CC_DIRECTOR->getVisibleOrigin();
}

void LevelSelection::initBackground()
{
    CCSprite* bg = CCSprite::create("GamePlay/Street.jpg");
    bg->setPosition(CCPoint{m_visibleSize.width*.5f + m_visibleOrigin.x,
                          m_visibleSize.height*.5f + m_visibleOrigin.y});
    this->addChild(bg, static_cast<int>(zOrder::zIndex_0));

}

void LevelSelection::initMenu()
{
    const int levels = GlobalColaboration::getInstance()->getAvaliablesLevels();
    m_menuItems = CCArray::createWithCapacity(levels);
    m_menuItems->retain();
    for (int i = 1; i <= 5; i++)
    {
        char filenameOff[40]{0};
        sprintf(filenameOff, "Interfaz/numero%d-of.png", i);
        char filenameOn[40]{0};
        sprintf(filenameOn, "Interfaz/numero%d-on.png", i);
        CCMenuItemImage *number = CCMenuItemImage::create(
            filenameOff,
            filenameOn,
            "Interfaz/lock.png",
            this,
            menu_selector(LevelSelection::menuPlayCallback));
        number->setTag(i);
        if (i > levels)
        {
            number->setEnabled(false);
        }

        number->setPosition (CCPoint{m_visibleSize.width*.65f - i%2*(m_visibleSize.width*.4f),
                                   m_visibleSize.height - i*m_visibleSize.height*.15f});

        m_menuItems->addObject(number);
    }

    CCMenuItemImage *pBackItem = CCMenuItemImage::create(
        "Interfaz/Flecha-of.png",
        "Interfaz/Flecha-on.png",
        this,
        menu_selector(LevelSelection::menuBackCallback));
    pBackItem->setPosition (CCPoint{m_visibleSize.width*.5f,
                                     m_visibleSize.height*.05f});
    m_menuItems->addObject(pBackItem);

    CCMenu *pMenu = CCMenu::createWithArray(m_menuItems);
    pMenu->setPosition(ccp(0.f, 0.f));
    this->addChild(pMenu, static_cast<int>(zOrder::zIndex_6));
}


/******************************************************************************/
/*                                 CALLBACKS                                  */
/******************************************************************************/
void LevelSelection::menuPlayCallback(CCObject* pSender)
{
    CC_DIRECTOR->pushScene(
        PlayerSelection::scene(
            static_cast<CCMenuItemImage*>(pSender)->getTag()));
}

void LevelSelection::menuBackCallback()
{
    CC_DIRECTOR->popScene();
}
