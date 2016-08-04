/*! \file CCMenuLayer.cpp
    \author <denisacostaq\@gmail.com>
    \date Fri Feb  7 20:10:41 CST 2014

    \brief This file become from: src/portable/scene/MainMenu/MenuLayer.cpp

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


#include "MenuLayer.h"
namespace MainMenu
{
/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/
MenuLayer::MenuLayer()
    : m_visibleSize {CCSize(0.f, 0.f)}
    , m_visibleOrigin {ccp(0.f, 0.f)}
    , m_playingAudio {false}
{
}

MenuLayer::~MenuLayer()
{
}

CCScene* MenuLayer::scene()
{
    CCScene *scene = CCScene::create();
    MenuLayer *layer = MenuLayer::create();
    scene->addChild(layer);
    return scene;
}


/******************************************************************************/
/*                                    INIT                                    */
/******************************************************************************/
bool MenuLayer::init ()
{
    if (!CCLayer::init())
    {
        return false;
    }

    initMembers();
    initBackground();
    initSounds();
    initMenu();

    return true;
}

void MenuLayer::initMembers ()
{
    m_visibleSize = CC_DIRECTOR->getVisibleSize();
    m_visibleOrigin = CC_DIRECTOR->getVisibleOrigin();
}

void MenuLayer::initBackground ()
{
    CCSprite *bg = CCSprite::create("Interfaz/BackGround.jpg");
    bg->setPosition(CCPoint{m_visibleSize.width*.5f + m_visibleOrigin.x,
                          m_visibleSize.height*.5f + m_visibleOrigin.y});
    this->addChild(bg, static_cast<int>(zOrder::zIndex_0));
}

void MenuLayer::initSounds()
{    
    if (GlobalColaboration::getInstance()->isAudioEnabled())
    {
        m_playingAudio = true;
        CC_AUDIO->preloadEffect("SOUND/torcs1_play.wav");
        CC_AUDIO->preloadBackgroundMusic("SOUND/torcs1Bg.mp3");
        CC_AUDIO->playBackgroundMusic("SOUND/torcs1Bg.mp3", true);
    }
}

void MenuLayer::initMenu()
{
    CCArray *pMenuItems = CCArray::create();

    CCMenuItemImage *pPlayItem = CCMenuItemImage::create(
        "Interfaz/play-of.png",
        "Interfaz/play-on.png",
        this,
        menu_selector(MenuLayer::menuPlayCallback));
    pPlayItem->setPosition (CCPoint{m_visibleSize.width*.5f,
                                  m_visibleSize.height*.65f});
    pMenuItems->addObject(pPlayItem);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    CCMenuItemImage *pInviteItem = CCMenuItemImage::create(
        "Interfaz/InviteBBS-of.png",
        "Interfaz/InviteBBS-on.png",
        CC_CALLBACK_0(MenuLayer::menuInviteBBFriendsCallback, this));
    pInviteItem->setPosition (CCPoint{m_visibleSize.width*.5f,
                                     m_visibleSize.height*.45f});
    pMenuItems->addObject (pInviteItem);
#endif //#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)


    CCMenuItemImage *pCreditsItem = CCMenuItemImage::create(
        "Interfaz/credits-of.png",
        "Interfaz/credits-on.png",
        this,
        menu_selector(MenuLayer::menuCreditsCallback));
    pCreditsItem->setPosition (CCPoint{m_visibleSize.width*.5f,
                                     m_visibleSize.height*.2f});
    pMenuItems->addObject (pCreditsItem);

    CCMenuItemImage *pExitItem = CCMenuItemImage::create(
        "Interfaz/cerrar-of.png",
        "Interfaz/cerrar-on.png",
        this,
        menu_selector(MenuLayer::menuExitCallback));
    pExitItem->setPosition (
        CCPoint{m_visibleSize.width - pExitItem->getContentSize().width*.5f,
              pExitItem->getContentSize().height*.5f});
    pMenuItems->addObject (pExitItem);


    CCMenuItemImage *pAudioTogleItem = CCMenuItemImage::create(
        "Interfaz/sound-of.png",
        "Interfaz/sound-on.png",
        this,
        menu_selector(MenuLayer::menuAudioTogleCallback));
    pAudioTogleItem->setPosition (
        CCPoint{m_visibleSize.width - pAudioTogleItem->getContentSize().width*1.5f,
              pAudioTogleItem->getContentSize().height*.5f});
    pMenuItems->addObject (pAudioTogleItem);

    CCMenu *pMenu = CCMenu::createWithArray (pMenuItems);
    pMenu->setPosition(ccp(0.f, 0.f));
    this->addChild(pMenu, static_cast<int>(zOrder::zIndex_1));
}


/******************************************************************************/
/*                                 CALLBACKS                                  */
/******************************************************************************/
void MenuLayer::menuPlayCallback ()
{
    if (m_playingAudio)
    {
        CC_AUDIO->playEffect("SOUND/torcs1_play.wav");
    }
    CC_DIRECTOR->pushScene(LevelSelection::scene());
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
void CCMenuLayer::menuInviteBBFriendsCallback()
{//TODO:
}
#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)

void MenuLayer::menuCreditsCallback()
{
    CC_DIRECTOR->pushScene(CCTransitionCrossFade::create(1.5f, CreditsLayer::scene()));
}

void MenuLayer::menuAudioTogleCallback()
{
    if (!GlobalColaboration::getInstance()->isAudioEnabled())
    {
        GlobalColaboration::getInstance()->setAudioEnabled(true);
        initSounds();
    }
    else
    {
        if (m_playingAudio)
        {

            m_playingAudio = false;
            CC_AUDIO->pauseBackgroundMusic();
            CC_AUDIO->pauseAllEffects();
        }
        else
        {
            m_playingAudio = true;
            CC_AUDIO->resumeBackgroundMusic();
            CC_AUDIO->resumeAllEffects();
        }
    }
}

void MenuLayer::menuExitCallback ()
{
    if (GlobalColaboration::getInstance()->isAudioEnabled())
    {
        CC_AUDIO->stopAllEffects();
        CC_AUDIO->unloadEffect("SOUND/torcs1_play.wav");
        CC_AUDIO->stopBackgroundMusic(true);
    }
    GlobalColaboration::getInstance()->setAudioEnabled(m_playingAudio);
    CC_AUDIO->end();
    this->stopAllActions();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CC_DIRECTOR->end();
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
#endif
}

}

