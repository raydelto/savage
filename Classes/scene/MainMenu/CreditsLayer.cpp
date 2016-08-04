/*! \file CreditsLayer.cpp
    \author <denisacostaq\@gmail.com>
    \date Tue Feb 11 05:19:08 CST 2014

    \brief This file become from: src/portable/scene/MainMenu/CreditsLayer.cpp

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

#include "CreditsLayer.h"

CreditsLayer::CreditsLayer()
    : m_visibleSize (CCSize(0.f, 0.f))
    , m_terrain (NULL)
{
}

CreditsLayer::~CreditsLayer()
{
    delete (m_terrain);
}

CCScene* CreditsLayer::scene()
{
    CCScene *scene = CCScene::create();
    CCLayer *layer = CreditsLayer::create();
    scene->addChild(layer);
    return scene;
}



bool CreditsLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }

    initMembers();
    initBackground();
    initMenu();
    initCredentials();

    m_terrain->setVelocity(150.f);
    this->schedule(schedule_selector(CreditsLayer::updatePutCar));
    this->schedule(schedule_selector(CreditsLayer::updatePutTree), .7f);

    return true;
}

void CreditsLayer::initMembers()
{
    m_visibleSize = CC_DIRECTOR->getVisibleSize();
    m_terrain = Terrain::create(kPlayer_1, Terrain::kLevel_1);
}

void CreditsLayer::initBackground()
{
    const CCArray * patchs = m_terrain->getPatchs();
    CCObject *patch = NULL;
    CCARRAY_FOREACH(patchs, patch) {
        this->addChild(static_cast<CCSprite*>(patch));
    }
    const CCArray * streets = m_terrain->getStreet();
    CCObject *street = NULL;
    CCARRAY_FOREACH(streets, street) {
        this->addChild(static_cast<CCSprite*>(street));
    }

    CCLayerColor *credentialsBackground = CCLayerColor::create(
                ccc4(0, 0, 0, 200),
                m_visibleSize.width*.9f,
                m_visibleSize.height*.8f);
    credentialsBackground->setPosition(
                CCPoint(m_visibleSize.width*.05f,
                      m_visibleSize.height*.1f));
    this->addChild(credentialsBackground, 1);


    const CCArray * cars = m_terrain->getCars();
    CCObject *car = NULL;
    CCARRAY_FOREACH(cars, car)
    {
        this->addChild(static_cast<Car*>(car));
    }

    const CCArray * trees = m_terrain->getTrees();
    CCObject *tree = NULL;
    CCARRAY_FOREACH(trees, tree)
    {
        this->addChild(static_cast<Tree*>(tree));
    }
}

void CreditsLayer::initCredentials()
{
    CCLabelTTF *company = CCLabelTTF::create("ASTTech",
                                        "FONT/Schwarzwald Regular.ttf",
                                        36.0f,
                                        CCSize(m_visibleSize.width*.9f,20.f),
                                        kCCTextAlignmentCenter,
                                        kCCVerticalTextAlignmentTop);
    company->setPosition(
                CCPoint(m_visibleSize.width*.5f,
                      m_visibleSize.height*.8f));
    this->addChild(company, 2);

    CCLabelTTF *gameIdea = CCLabelTTF::create("Game Idea:",
                                        "FONT/Schwarzwald Regular.ttf",
                                        32.0f,
                                        CCSize(m_visibleSize.width*.9f,20.f),
                                        kCCTextAlignmentCenter,
                                        kCCVerticalTextAlignmentTop);
    gameIdea->setPosition(
                CCPoint(m_visibleSize.width*.5f,
                      m_visibleSize.height*.65f));
    this->addChild(gameIdea, 2);

    CCLabelTTF *gdsram = CCLabelTTF::create("gdsram@gmail.com",
                                        "FONT/Schwarzwald Regular.ttf",
                                        20.0f,
                                        CCSize(m_visibleSize.width*.9f,20.f),
                                        kCCTextAlignmentLeft,
                                        kCCVerticalTextAlignmentTop);
    gdsram->setPosition(
                CCPoint(m_visibleSize.width*.55f,
                      m_visibleSize.height*.58f));
    this->addChild(gdsram, 2);

    CCLabelTTF *developers = CCLabelTTF::create("Developers:",
                                        "FONT/Schwarzwald Regular.ttf",
                                        32.0f,
                                        CCSize(m_visibleSize.width*.9f,20.f),
                                        kCCTextAlignmentCenter,
                                        kCCVerticalTextAlignmentTop);
    developers->setPosition(
                CCPoint(m_visibleSize.width*.5f,
                      m_visibleSize.height*.48f));
    this->addChild(developers, 2);

    CCLabelTTF *yop = CCLabelTTF::create("deniacostaq@gmail.com",
                                        "FONT/Schwarzwald Regular.ttf",
                                        20.0f,
                                        CCSize(m_visibleSize.width*.9f,20.f),
                                        kCCTextAlignmentLeft,
                                        kCCVerticalTextAlignmentTop);
    yop->setPosition(
                CCPoint(m_visibleSize.width*.55f,
                      m_visibleSize.height*.41f));
    this->addChild(yop, 2);

    CCLabelTTF *raydelto = CCLabelTTF::create("raydelto@gmail.com",
                                        "FONT/Schwarzwald Regular.ttf",
                                        20.0f,
                                        CCSize(m_visibleSize.width*.9f,20.f),
                                        kCCTextAlignmentLeft,
                                        kCCVerticalTextAlignmentTop);
    raydelto->setPosition(
                CCPoint(m_visibleSize.width*.55f,
                      m_visibleSize.height*.36f));
    this->addChild(raydelto, 2);

    CCLabelTTF *design = CCLabelTTF::create("Design:",
                                        "FONT/Schwarzwald Regular.ttf",
                                        32.0f,
                                        CCSize(m_visibleSize.width*.9f,20.f),
                                        kCCTextAlignmentCenter,
                                        kCCVerticalTextAlignmentTop);
    design->setPosition(
                CCPoint(m_visibleSize.width*.5f,
                      m_visibleSize.height*.26f));
    this->addChild(design, 2);

    CCLabelTTF *rulo = CCLabelTTF::create("rfarencibia@gmail.com",
                                        "FONT/Schwarzwald Regular.ttf",
                                        20.0f,
                                        CCSize(m_visibleSize.width*.9f,20.f),
                                        kCCTextAlignmentLeft,
                                        kCCVerticalTextAlignmentTop);
    rulo->setPosition(
                CCPoint(m_visibleSize.width*.55f,
                      m_visibleSize.height*.19f));
    this->addChild(rulo, 2);
}

void CreditsLayer::initMenu()
{
    CCMenuItemImage *pBackItem = CCMenuItemImage::create(
        "Interfaz/Flecha-of.png",
        "Interfaz/Flecha-on.png",
        this,
        menu_selector(CreditsLayer::menuBackCallback));
    pBackItem->setPosition (CCPoint(m_visibleSize.width*.5f,
                                     m_visibleSize.height*.05f));
    CCMenu *pMenu = CCMenu::createWithItem(pBackItem);
    pMenu->setPosition(ccp(0.f, 0.f));
    this->addChild(pMenu, static_cast<int>(zIndex_2));

}

void CreditsLayer::updatePutCar(float dt)
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

void CreditsLayer::updatePutTree(float dt)
{
    m_terrain->putTree();
}

void CreditsLayer::menuBackCallback()
{
    this->unschedule(schedule_selector(CreditsLayer::updatePutCar));
    this->unschedule(schedule_selector(CreditsLayer::updatePutTree));
    m_terrain->stopTerrain();
    CC_DIRECTOR->popScene();
}
