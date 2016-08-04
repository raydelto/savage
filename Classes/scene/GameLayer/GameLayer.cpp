/*! \file GameLayer.cpp
    \author <denisacostaq\@gmail.com>
    \date Fri Feb  7 18:33:16 CST 2014

    \brief This file become from: src/portable/scene/GameLayer.cpp

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

#include "GameLayer.h"

/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/
GameLayer::GameLayer()
    : m_visibleSize (CCSize(0.f, 0.f))
    , m_visibleOrigin (ccp(0.f, 0.f))
    , m_terrain (NULL)
    , m_cTimerValue(60)
    , m_timmer (m_cTimerValue)
    , m_timmerLabel (NULL)
    , m_gameStatus (Terrain::kPlaying)
    , m_currentLevel (1)
    , m_pointOfTouchBegan (ccp(0.f, 0.f))
    , m_movinTouch (false)
    , m_goToPlay (NULL)
    , m_wine (NULL)
    , m_fail (NULL)
    , m_menu (NULL)
    , m_pMenuOnPause (NULL)
    , m_animImpact (NULL)
    , m_Exp0020 (NULL)
{
}

GameLayer::~GameLayer()
{
    CC_SAFE_RELEASE(m_timmerLabel);
    CC_SAFE_RELEASE(m_goToPlay);
    CC_SAFE_RELEASE(m_wine);
    CC_SAFE_RELEASE(m_fail);
    CC_SAFE_RELEASE(m_menu);
    CC_SAFE_RELEASE(m_pMenuOnPause);
    CC_SAFE_RELEASE(m_animImpact);
    CC_SAFE_RELEASE(m_Exp0020);

    delete(m_terrain);
}


/******************************************************************************/
/*                                    INIT                                    */
/******************************************************************************/
bool GameLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    else
    {
        initMembers();
        initMenu();
        goToPlay();
        return true;
    }
}

void GameLayer::initMembers()
{
    m_visibleSize = CC_DIRECTOR->getVisibleSize();
    m_visibleOrigin = CC_DIRECTOR->getVisibleOrigin();

    m_timmerLabel = CCLabelTTF::create("0", "Felt", m_visibleSize.width/15);
    m_timmerLabel->retain();
    m_timmerLabel->setAnchorPoint (CCPoint(1.0f, 1.0f));
    m_timmerLabel->setColor(ccc3(250, 236, 0));
    m_timmerLabel->setString("60");
    m_timmerLabel->setPosition (
        CCPoint(m_visibleSize.width - m_timmerLabel->getContentSize().width,
              m_visibleSize.height));
    this->addChild (m_timmerLabel, static_cast<int>(zIndex_6));
    m_timmerLabel->runAction(
        CCRepeatForever::create(
            CCSequence::createWithTwoActions(
                CCDelayTime::create(1.0f),
                CCCallFunc::create(
                    this, callfunc_selector(GameLayer::updateTimmer)))));

    m_goToPlay = CCSprite::create("Interfaz/go!!.png");
    m_goToPlay->retain();
    this->addChild(m_goToPlay, static_cast<int>(zIndex_6));
    m_goToPlay->setPosition(CCPoint(m_visibleSize.width*.5f,
                          m_visibleSize.height*.5f));


    m_wine = CCSprite::create("Interfaz/You-win.png");
    m_wine->retain();
    m_wine->setScale(.1f);
    this->addChild(m_wine, static_cast<int>(zIndex_6));
    m_wine->setPosition(CCPoint(m_visibleSize.width*.5f,
                            m_visibleSize.height*.5f));


    m_fail = CCSprite::create("Interfaz/you-failed.png");
    m_fail->retain();
    m_fail->setScale(.1f);
    m_fail->setPosition(CCPoint(m_visibleSize.width*.5f,
                            m_visibleSize.height*.5f));
    this->addChild(m_fail, static_cast<int>(zIndex_6));

    CCObject *it = NULL;
    const CCArray *str = m_terrain->getPatchs();
    CCARRAY_FOREACH(str, it)
    {
        this->addChild(static_cast<CCNode*>(it), static_cast<int>(zIndex_0));
    }

    str = m_terrain->getStreet();
    CCARRAY_FOREACH(str, it)
    {
        this->addChild(static_cast<CCNode*>(it), static_cast<int>(zIndex_1));
    }

    str = m_terrain->getTrees();
    CCARRAY_FOREACH(str, it)
    {
        this->addChild(static_cast<CCNode*>(it), static_cast<int>(zIndex_5));
    }

    str = m_terrain->getObstacles();
    CCARRAY_FOREACH(str, it)
    {
        this->addChild(static_cast<CCNode*>(it), static_cast<int>(zIndex_2));
    }

    str = m_terrain->getCars();
    CCARRAY_FOREACH(str, it)
    {
        this->addChild(static_cast<CCNode*>(it), static_cast<int>(zIndex_3));
    }

    Player *ptrToPlayer = const_cast<Player*>(m_terrain->getPlayer());
    this->addChild(ptrToPlayer, static_cast<int>(zIndex_3));

    this->setTouchMode(kCCTouchesOneByOne);
    this->setTouchEnabled(true);


    CCSpriteFrameCache::sharedSpriteFrameCache()->
            addSpriteFramesWithFile ("IMG/Explosion_Sprites/Explosion_Sprites.plist");
    this->addChild (CCSpriteBatchNode::create("IMG/Explosion_Sprites/Explosion_Sprites.png"));

    CCSpriteFrame *frame = NULL;//NOTE: ver en google style guide
    m_animImpact = CCAnimation::create();
    m_animImpact->retain();
    for(int i = 1; i < 10; i++)
    {
        char szName[100] = {0};
        sprintf(szName, "Exp000%d.png", i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);
        m_animImpact->addSpriteFrame(frame);
    }
    for(int i = 10; i <= 20; i++)
    {
        char szName[100] = {0};
        sprintf(szName, "Exp00%d.png", i);
        frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);
        m_animImpact->addSpriteFrame(frame);
    }
    m_animImpact->setDelayPerUnit(.9f / 20.f);
    m_animImpact->setRestoreOriginalFrame(true);

    m_Exp0020 = CCSprite::create("IMG/Explosion_Sprites/Exp0020.png");
    m_Exp0020->retain();
    this->addChild(m_Exp0020, static_cast<int>(zIndex_5));
    m_Exp0020->setVisible(false);
}

void GameLayer::initMenu()
{
    CCMenuItemImage *pauseItem = CCMenuItemImage::create(
                "Interfaz/Pause-of.png",
                "Interfaz/pause-on.png",
                this,
                menu_selector(GameLayer::menuPauseCallback));
    pauseItem->setPosition(
                CCPoint(-m_visibleSize.width*.5f +
                            pauseItem->getContentSize().width*.5f,
                      m_visibleSize.height*.5f -
                            pauseItem->getContentSize().height*.5f));

    m_menu = CCMenu::createWithItem(pauseItem);
    m_menu->retain();
    this->addChild(m_menu, static_cast<int>(zIndex_5));


    CCArray *onPauseItems = CCArray::create();

    CCMenuItemImage *exitItem = CCMenuItemImage::create(
                "Interfaz/Flecha-of.png",
                "Interfaz/Flecha-on.png",
                this,
                menu_selector(GameLayer::menuExitCallback));
    exitItem->setPositionX(-1.2f*exitItem->getContentSize().width);
    onPauseItems->addObject(exitItem);

    CCMenuItemImage *resumeItem = CCMenuItemImage::create(
                "Interfaz/Flecha-of.png",
                "Interfaz/Flecha-on.png",
                this,
                menu_selector(GameLayer::menuResumeCallback));
    resumeItem->setPositionX(1.2f*resumeItem->getContentSize().width);
    onPauseItems->addObject(resumeItem);


    m_pMenuOnPause = CCMenu::createWithArray(onPauseItems);
    m_pMenuOnPause->retain();
    m_pMenuOnPause->setVisible(false);
    this->addChild(m_pMenuOnPause, static_cast<int>(zIndex_6));
}

void GameLayer::win()
{
    if(m_currentLevel == GlobalColaboration::getInstance()->getAvaliablesLevels())
    {
        GlobalColaboration::getInstance()->setAvaliablesLevels(m_currentLevel + 1);
    }
    CC_DIRECTOR->popScene();
    CC_DIRECTOR->popScene();
}


/******************************************************************************/
/*                                  UPDATE                                    */
/******************************************************************************/
void GameLayer::goToPlay()
{
    m_fail->setVisible(false);
    m_wine->setVisible(false);
    m_goToPlay->setVisible(true);
    m_goToPlay->setScale(.5f);
    m_goToPlay->runAction(CCFadeOut::create(2.5f));
    m_goToPlay->runAction(
        CCSequence::createWithTwoActions(
            CCScaleTo::create(2.5f, 10.0f),
            CCCallFunc::create(this, callfunc_selector(GameLayer::initGame))));

    m_terrain->setVelocity(.0f);
}

void GameLayer::putObstacle(float dt)
{
    m_terrain->putObstacle();
}

void GameLayer::putTree(float dt)
{
    m_terrain->putTree();
}

void GameLayer::putCar(float dt)
{
    Car* car = m_terrain->getAndActiveRandomCar();
    if (car != NULL)
    {
        switch (GlobalColaboration::getInstance()->getRandomIntegerInRange(0, 3))
        {
        case 0:
            car->setFootpath(Car::kCenter);
            break;
        case 1:
            car->setFootpath(Car::kLeft);
            break;
        case 2:
            car->setFootpath(Car::kRigth);
            break;
        default:
            break;
        }
        m_terrain->putCar(car);
    }
}

void GameLayer::update(float dt)
{
    m_gameStatus = m_terrain->update();
    switch (m_gameStatus)
    {
    case Terrain::kGameOver:
        this->unschedule(schedule_selector(GameLayer::update));
        this->unschedule(schedule_selector(GameLayer::putCar));
        this->unschedule(schedule_selector(GameLayer::putObstacle));
        this->unschedule(schedule_selector(GameLayer::putTree));

        m_Exp0020->setVisible(true);
        m_Exp0020->setPosition(const_cast<Player*>(m_terrain->getPlayer())->getPosition());
        m_Exp0020->runAction(
            CCSequence::createWithTwoActions(
                CCAnimate::create(static_cast<CCAnimation*>(m_animImpact->copy())),
                CCCallFunc::create(this, callfunc_selector(GameLayer::gameOver))));
        this->schedule(schedule_selector(GameLayer::updateexplosioPosition), .03f);
        break;
    case Terrain::kCollided:
        m_timmer = m_cTimerValue;
        break;
    default:
        break;
    }
}

void GameLayer::updateexplosioPosition(float dt)
{
    Player *p = const_cast<Player*>(m_terrain->getPlayer());
    m_Exp0020->setPosition(
        CCPoint(p->getPositionX(),
                p->getPositionY() + p->getContentSize().height*.47f));
}

void GameLayer::updateTimmer()
{
    if (m_timmer-- == 0)
    {
        this->unschedule(schedule_selector(GameLayer::update));
        this->unschedule(schedule_selector(GameLayer::putCar));
        this->unschedule(schedule_selector(GameLayer::putObstacle));
        this->unschedule(schedule_selector(GameLayer::putTree));

        m_wine->setVisible(true);
        m_wine->runAction(CCScaleTo::create(2.f , 2.f));
        m_wine->runAction(
                    CCSequence::createWithTwoActions(
                        CCFadeIn::create(2.f),
                        CCCallFunc::create(this, callfunc_selector(GameLayer::win))));
        m_timmer = 0;
        m_timmerLabel->pauseSchedulerAndActions();
    }
    else
    {
        char timmerChars[5] = {};
        sprintf(timmerChars, "%d", m_timmer);
        m_timmerLabel->setString(timmerChars);
    }
}

void GameLayer::gameOver()
{
    this->unschedule(schedule_selector(GameLayer::updateexplosioPosition));
    m_Exp0020->setVisible(false);
    m_timmerLabel->pauseSchedulerAndActions();

    m_fail->setVisible(true);
    m_fail->runAction(CCRepeat::create(CCRotateBy::create(1.0f, 360.0f), 2));
    m_fail->runAction(CCFadeIn::create(2.0f));
    m_fail->runAction(CCSequence::createWithTwoActions(
        CCScaleTo::create(2.0f, 1.0f),
        CCSequence::createWithTwoActions(
            CCFadeOut::create(1.0f),
            CCCallFunc::create(this, callfunc_selector(GameLayer::goToPlay)))));
}


/******************************************************************************/
/*                                 CALLBACKS                                  */
/******************************************************************************/
bool GameLayer::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
    m_pointOfTouchBegan = touch->getLocation();
    return m_gameStatus != Terrain::kGameOver &&
            m_menu->isVisible();
}

void GameLayer::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
    m_movinTouch = true;
}

void GameLayer::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
    if (m_movinTouch)
    {
        m_movinTouch = false;
        float veticalComponent = m_pointOfTouchBegan.y - touch->getLocation().y;
        float horizontalComponent = m_pointOfTouchBegan.x - touch->getLocation().x;
        if (abs (veticalComponent) > abs(horizontalComponent))
        {
            if (veticalComponent < 0)
            {
                m_terrain->setVelocity(
                    m_terrain->getVelocity() +
                    (abs (veticalComponent) / m_visibleSize.height) * 300.0f);
            }
            else
            {
                m_terrain->setVelocity(
                    m_terrain->getVelocity() -
                    (abs (veticalComponent) / m_visibleSize.height) * 300.0f);
            }
        }
        else
        {
            if (horizontalComponent > 0)
             {
                int fp = m_terrain->getPlayer()->getFootpath();
                if (fp == Car::kCenter)
                {
                    m_terrain->changeFootpathTo (Car::kLeft);
                }
                else if (fp == Car::kRigth)
                {
                    if (horizontalComponent > m_visibleSize.width*.5f)
                    {
                        m_terrain->changeFootpathTo (Car::kLeft);
                    }
                    else
                    {
                        m_terrain->changeFootpathTo (Car::kCenter);
                    }
                }

             }
             else
             {
                horizontalComponent *= -1;
                int fp = m_terrain->getPlayer()->getFootpath();
                if (fp == Car::kCenter)
                {
                    m_terrain->changeFootpathTo (Car::kRigth);
                }
                else
                {
                    if (horizontalComponent > m_visibleSize.width*.5f)
                    {
                        m_terrain->changeFootpathTo (Car::kRigth);
                    }
                    else
                    {
                        m_terrain->changeFootpathTo (Car::kCenter);
                    }
                }
             }
        }
    }
}

void GameLayer::pauseGame()
{
    CCActionManager* actionManager = CCDirector::sharedDirector()->getActionManager();
    actionManager->pauseTarget(m_goToPlay);
    actionManager->pauseTarget(m_Exp0020);
    actionManager->pauseTarget(m_wine);
    actionManager->pauseTarget(m_fail);
    actionManager->pauseTarget(m_timmerLabel);
    m_terrain->pauseTerrain();
    this->pauseSchedulerAndActions();
    CC_AUDIO->pauseAllEffects();
    CC_AUDIO->pauseBackgroundMusic();
}

void GameLayer::resumeGame()
{
    CC_AUDIO->resumeBackgroundMusic();
    CC_AUDIO->resumeAllEffects();
    this->resumeSchedulerAndActions();
    m_terrain->resumeTerrain();
    CCActionManager* actionManager = CCDirector::sharedDirector()->getActionManager();
    actionManager->resumeTarget(m_timmerLabel);
    actionManager->resumeTarget(m_fail);
    actionManager->resumeTarget(m_wine);
    actionManager->resumeTarget(m_Exp0020);
    actionManager->resumeTarget(m_goToPlay);
}

void GameLayer::menuPauseCallback()
{
    m_pMenuOnPause->setVisible(true);
    m_menu->setVisible(false);
    pauseGame();
}
void GameLayer::menuExitCallback()
{
    menuResumeCallback();
    stopGame();
    CC_DIRECTOR->popScene();
    CC_DIRECTOR->popScene();
}

void GameLayer::menuResumeCallback()
{
    resumeGame();
    m_menu->setVisible(true);
    m_pMenuOnPause->setVisible(false);
}

void GameLayer::stopGame()
{
    m_goToPlay->stopAllActions();
    m_Exp0020->stopAllActions();
    m_wine->stopAllActions();
    m_fail->stopAllActions();
    m_timmerLabel->stopAllActions();
    m_terrain->stopTerrain();
    this->stopAllActions();
    this->unschedule(schedule_selector(GameLayer::update));
    this->unschedule(schedule_selector(GameLayer::putCar));
    this->unschedule(schedule_selector(GameLayer::putObstacle));
    this->unschedule(schedule_selector(GameLayer::putTree));
    this->unschedule(schedule_selector(GameLayer::updateexplosioPosition));
    CC_AUDIO->stopAllEffects();
    CC_AUDIO->stopBackgroundMusic();

    //SpriteFrameCache::getInstance()->removeSpriteFrames();FIXME: if use this, cause a memory leak
}
