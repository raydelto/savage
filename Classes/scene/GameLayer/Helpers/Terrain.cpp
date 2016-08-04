/*! \file Terrain.cpp
    \author <denisacostaq\@gmail.com>
    \date Sat Feb  8 00:51:59 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/Helpers/Terrain.cpp

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

#include "Terrain.h"

/******************************************************************************/
/*                                   MEMORY                                   */
/******************************************************************************/
Terrain::Terrain(const PlayerKind &selectedPlayer,
                 const Level &selectedLevel)
 : m_visibleSize (CCSize(0.f, 0.f))
 , m_street (NULL)
 , m_patchs (NULL)
 , m_cMaxSegmentsNumber(3)
 , m_velocity (0.0f)
 , m_player (NULL)
 , m_selectedLevel (selectedLevel)
 , m_trees (NULL)
 , m_obstacles (NULL)
 , m_treesIdle(0)
 , m_obstaclesIdle(0)
 , m_carsIdle (0)
 , m_gc (GlobalColaboration::getInstance())
 , m_cars (NULL)
 , m_selectedPlayer (selectedPlayer)
 , m_mapObstaclesPlayerCollitions ()
 , m_mapCarsPlayerCollitions ()
 , m_mapCarsObstaclesCollitions ()
{
}

Terrain::~Terrain()
{
    CC_SAFE_RELEASE(m_street);
    CC_SAFE_RELEASE(m_patchs);
    CC_SAFE_RELEASE(m_player);
    CC_SAFE_RELEASE(m_trees);
    CC_SAFE_RELEASE(m_obstacles);
    CC_SAFE_RELEASE(m_cars);

    m_mapObstaclesPlayerCollitions.clear();
    m_mapCarsPlayerCollitions.clear();
    m_mapCarsObstaclesCollitions.clear();
}

Terrain* Terrain::create(const PlayerKind &selectedPlayer,
                         const Level &selectedLevel)
{
    Terrain *pRet = new Terrain(selectedPlayer, selectedLevel);
    if (pRet && pRet->init())
    {
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


/******************************************************************************/
/*                                    INIT                                    */
/******************************************************************************/
bool Terrain::init()
{
    initMembers();
    initStreet();
    initTrees();
    initPlayer();
    initObstacles();
    initCars();

    CCObject *itCars = NULL;
    CCARRAY_FOREACH(m_cars, itCars)
    {
        CCObject *itObstacles = NULL;
        CCARRAY_FOREACH(m_obstacles, itObstacles)
        {
            m_mapCarsObstaclesCollitions.insert(
                        std::pair<Collition, bool>(Collition(itObstacles, itCars), false));
        }
    }
    return true;
}

void Terrain::initMembers()
{
    m_visibleSize = CC_DIRECTOR->getVisibleSize();

    m_footpathPoints.push_back(CCPoint(m_visibleSize.width*.3f,0.0f));
    m_footpathPoints.push_back(CCPoint(m_visibleSize.width*.5f,0.0f));
    m_footpathPoints.push_back(CCPoint(m_visibleSize.width*.69f,0.0f));
}

void Terrain::initStreet()
{
    m_street = CCArray::createWithCapacity (m_cMaxSegmentsNumber);
    m_street->retain ();
    m_patchs = CCArray::createWithCapacity (m_cMaxSegmentsNumber);
    m_patchs->retain ();
    CCPoint anchorPoint = ccp(0.f, 0.f);

    char filename[40];
    for (int index = 0; index < 40; index++) {
      filename[index] = 0;
    }
    if(m_selectedLevel == kLevel_1 || m_selectedLevel == kLevel_2)
    {
        sprintf (filename, "GamePlay/Street Beach.jpg");
    }
    else
    {
        sprintf (filename, "GamePlay/Street.jpg");
    }
    CCSprite *street = NULL;
    CCSprite *patch = NULL;
    for (int i = 0; i < m_cMaxSegmentsNumber; i++)
    {
        street = CCSprite::create (filename);
        street->setAnchorPoint (anchorPoint);
        street->setPositionX (0.0f);
        m_street->addObject (street);

        patch = CCSprite::create (filename);
        patch->setAnchorPoint (anchorPoint);
        patch->setPositionX (0.0f);
        m_patchs->addObject (patch);

        putFragmentBack (i, i * street->getContentSize().height);
    }
}

void Terrain::initTrees()
{
    m_trees = CCArray::create();
    m_trees->retain();
    if (m_selectedLevel == kLevel_1 || m_selectedLevel == kLevel_2)
    {
        Tree *tree = NULL;

        tree = Tree::create("Arboles/1.png");
        tree->setKind(Body::kTree);
        tree->setLeft(m_visibleSize.width*.1f);
        tree->setRigth(m_visibleSize.width*.157f);
        tree->setVisible(false);
        m_trees->addObject(tree);

        tree = Tree::create("Arboles/2.png");
        tree->setKind(Body::kTree);
        tree->setLeft(m_visibleSize.width*.15f);
        tree->setRigth(m_visibleSize.width*.9f);
        tree->setVisible(false);
        m_trees->addObject(tree);

        tree = Tree::create("Arboles/3.png");
        tree->setKind(Body::kTree);
        tree->setLeft(m_visibleSize.width*.95f);
        tree->setRigth(m_visibleSize.width*.9f);
        tree->setVisible(false);
        m_trees->addObject(tree);

        tree = Tree::create("Arboles/Arbol1.png");
        tree->setKind(Body::kTree);
        tree->setLeft(m_visibleSize.width*.1f);
        tree->setRigth(m_visibleSize.width*.9f);
        tree->setVisible(false);
        m_trees->addObject(tree);

        tree = Tree::create("Arboles/arbol2.png");
        tree->setKind(Body::kTree);
        tree->setLeft(m_visibleSize.width*.95f);
        tree->setRigth(m_visibleSize.width*.9f);
        tree->setVisible(false);
        m_trees->addObject(tree);


        tree = Tree::create("Arboles/trees.png");
        tree->setKind(Body::kTree);
        tree->setLeft(m_visibleSize.width*.9f);
        tree->setRigth(m_visibleSize.width*.95f);
        tree->setVisible(false);
        m_trees->addObject(tree);
    }
    else
    {
        Tree *tree = NULL;

        tree = Tree::create("Arboles/2.png");
        tree->setKind(Body::kTree);
        tree->setLeft(m_visibleSize.width*.15f);
        tree->setRigth(m_visibleSize.width*.8f);
        tree->setVisible(false);
        m_trees->addObject(tree);

        tree = Tree::create("Arboles/3.png");
        tree->setKind(Body::kTree);
        tree->setLeft(m_visibleSize.width*.2f);
        tree->setRigth(m_visibleSize.width*.9f);
        tree->setVisible(false);
        m_trees->addObject(tree);

        tree = Tree::create("Arboles/5.png");
        tree->setKind(Body::kTree);
        tree->setLeft(m_visibleSize.width*.1f);
        tree->setRigth(m_visibleSize.width*.9f);
        tree->setVisible(false);
        m_trees->addObject(tree);

        tree = Tree::create("Arboles/Arbol1.png");
        tree->setKind(Body::kTree);
        tree->setLeft(m_visibleSize.width*.1f);
        tree->setRigth(m_visibleSize.width*.8f);
        tree->setVisible(false);
        m_trees->addObject(tree);
    }
    m_treesIdle = m_trees->count();
}

void Terrain::initObstacles()
{
    m_obstacles = CCArray::create();
    m_obstacles->retain();
    if (m_selectedLevel == kLevel_1)
    {
        Obstacle *obstacle = NULL;

        obstacle = Obstacle::create("GamePlay/Gomas.png");
        obstacle->setKind(Body::kGomas);
        obstacle->setVisible(false);
        m_obstacles->addObject(obstacle);

        obstacle = Obstacle::create("GamePlay/Tanque-de-Basura.png");
        obstacle->setKind(Body::kBasurero);
        obstacle->setVisible(false);
        m_obstacles->addObject(obstacle);
    }
    else
    {
        Obstacle *obstacle = Obstacle::create("GamePlay/Charco-de-Aceite.png");
        obstacle->setKind(Body::kAceite);
        obstacle->setVisible(false);
        m_obstacles->addObject(obstacle);

        obstacle = Obstacle::create("GamePlay/Gomas.png");
        obstacle->setKind(Body::kGomas);
        obstacle->setVisible(false);
        m_obstacles->addObject(obstacle);

        obstacle = Obstacle::create("GamePlay/Tanque-de-Basura.png");
        obstacle->setKind(Body::kBasurero);
        obstacle->setVisible(false);
        m_obstacles->addObject(obstacle);

        if (m_selectedLevel == kLevel_5)
        {
            obstacle = Obstacle::create("GamePlay/Gomas.png");
            obstacle->setKind(Body::kGomas);
            obstacle->setVisible(false);
            m_obstacles->addObject(obstacle);

            obstacle = Obstacle::create("GamePlay/Charco-de-Aceite.png");
            obstacle->setKind(Body::kAceite);
            obstacle->setVisible(false);
            m_obstacles->addObject(obstacle);
        }
    }
    m_obstaclesIdle = m_obstacles->count();

    CCObject *it = NULL;
    CCARRAY_FOREACH(m_obstacles, it)
    {
        m_mapObstaclesPlayerCollitions.insert(
                    std::pair<Collition, bool>(Collition(m_player, it), false));
    }
}

void Terrain::initCars()
{
    m_cars = CCArray::create();
    m_cars->retain();
    if (m_selectedLevel == kLevel_1)
    {
        Car *car = NULL;

        car = Car::create("GamePlay/Camioneta.png");
        car->setKind(Body::kCar);
        car->setVelocity(60.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = Car::create("GamePlay/Jeep.png");
        car->setKind(Body::kCar);
        car->setVelocity(70.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = Car::create("GamePlay/Jeep.png");
        car->setKind(Body::kCar);
        car->setVelocity(70.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = CarWithPerspective::create("GamePlay/Guagua-Izquierda.png");
        car->setKind(Body::kCar);
        car->setVelocity(100.0f);
        car->setVisible(false);
        m_cars->addObject(car);

    }
    else if (m_selectedLevel == kLevel_2)
    {
        Car *car = NULL;

        car = Car::create("GamePlay/Camioneta.png");
        car->setKind(Body::kCar);
        car->setVelocity(60.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = Car::create("GamePlay/Jeep.png");
        car->setKind(Body::kCar);
        car->setVelocity(70.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = Car::create("GamePlay/Jeep.png");
        car->setKind(Body::kCar);
        car->setVelocity(70.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = CarWithPerspective::create("GamePlay/Guagua-Izquierda.png");
        car->setKind(Body::kCar);
        car->setVelocity(100.0f);
        car->setVisible(false);
        m_cars->addObject(car);
    }
    else if (m_selectedLevel == kLevel_3)
    {
        Car *car = NULL;

        car = Car::create("GamePlay/Camioneta.png");
        car->setKind(Body::kCar);
        car->setVelocity(60.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = Car::create("GamePlay/Jeep.png");
        car->setKind(Body::kCar);
        car->setVelocity(70.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = CarWithPerspective::create("GamePlay/Guagua-Izquierda.png");
        car->setKind(Body::kCar);
        car->setVelocity(100.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = CarWithPerspective::create("GamePlay/Guagua-Izquierda.png");
        car->setKind(Body::kCar);
        car->setVelocity(100.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = Car::create("GamePlay/Rastra.png");
        car->setKind(Body::kCar);
        car->setVelocity(200.0f);
        car->setVisible(false);
        m_cars->addObject(car);
    }
    else if (m_selectedLevel == kLevel_4)
    {
        Car *car = NULL;

        car = Car::create("GamePlay/Camioneta.png");
        car->setKind(Body::kCar);
        car->setVelocity(70.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = Car::create("GamePlay/Jeep.png");
        car->setKind(Body::kCar);
        car->setVelocity(80.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = CarWithPerspective::create("GamePlay/Guagua-Izquierda.png");
        car->setKind(Body::kCar);
        car->setVelocity(110.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = Car::create("GamePlay/Rastra.png");
        car->setKind(Body::kCar);
        car->setVelocity(210.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = CarWithPerspective::create("GamePlay/Guagua-Izquierda.png");
        car->setKind(Body::kCar);
        car->setVelocity(110.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = Car::create("GamePlay/Rastra.png");
        car->setKind(Body::kCar);
        car->setVelocity(210.0f);
        car->setVisible(false);
        m_cars->addObject(car);

    }
    else if (m_selectedLevel == kLevel_5)
    {
        Car *car = NULL;

        car = Car::create("GamePlay/Camioneta.png");
        car->setKind(Body::kCar);
        car->setVelocity(80.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = Car::create("GamePlay/Camioneta.png");
        car->setKind(Body::kCar);
        car->setVelocity(180.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = Car::create("GamePlay/Jeep.png");
        car->setKind(Body::kCar);
        car->setVelocity(90.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = CarWithPerspective::create("GamePlay/Guagua-Izquierda.png");
        car->setKind(Body::kCar);
        car->setVelocity(120.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = Car::create("GamePlay/Rastra.png");
        car->setKind(Body::kCar);
        car->setVelocity(220.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = Car::create("GamePlay/Rastra.png");
        car->setKind(Body::kCar);
        car->setVelocity(220.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = CarWithPerspective::create("GamePlay/Guagua-Izquierda.png");
        car->setKind(Body::kCar);
        car->setVelocity(120.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = CarWithPerspective::create("GamePlay/Guagua-Izquierda.png");
        car->setKind(Body::kCar);
        car->setVelocity(60.0f);
        car->setVisible(false);
        m_cars->addObject(car);

        car = Car::create("GamePlay/Rastra.png");
        car->setKind(Body::kCar);
        car->setVelocity(240.0f);
        car->setVisible(false);
        m_cars->addObject(car);
    }

    m_carsIdle = m_cars->count();

    CCObject* it = NULL;
    CCARRAY_FOREACH (m_cars, it)
    {
        m_mapCarsPlayerCollitions.insert(
                    std::pair<Collition, bool>(Collition(m_player, it), false));
    }
}

void Terrain::initPlayer()
{
    m_player = Player::create(m_selectedPlayer);
    m_player->retain();
    m_player->setPosition(m_footpathPoints[1]);
    m_player->setPositionY(100.0f);
    m_player->setVelocity(100.0f);
    this->setVelocity(m_player->getVelocity());
}

void Terrain::putFragmentBack(int fragmentIndex, float fromY)
{
    CCSprite *fragment = static_cast<CCSprite*>(
                m_street->objectAtIndex (fragmentIndex));
    fragment->stopAllActions();
    fragment->setPositionY(fromY);
    float interval = getInterval(fragment->getPositionY(),
                                 -1.5f * fragment->getContentSize().height,
                                 0.0f);
    CCSequence *seq = CCSequence::createWithTwoActions (
        CCMoveTo::create (
            interval,
            CCPoint(fragment->getPositionX(),
                  -1.5f * fragment->getContentSize().height)),
        CCCallFuncN::create (this, callfuncN_selector(Terrain::repositioneTerrain)));
    fragment->runAction (seq);



    fragment = static_cast<CCSprite*>(
                m_patchs->objectAtIndex (fragmentIndex));
    fragment->stopAllActions();
    fragment->setPositionY(fromY + fragment->getContentSize().height*.5f);
    fragment->runAction(
        CCMoveTo::create (
            interval,
            CCPoint(fragment->getPositionX(),
                  -fragment->getContentSize().height)));
}

float Terrain::getInterval (const float &begin,
                            const float &end,
                            float selfVelocity)
{
    return (begin - end)/(m_velocity + selfVelocity);
}

void Terrain::repositioneTerrain (CCObject *pSender)
{
    if (!pSender)
    {
        exit (EXIT_SUCCESS);
    }
    if (!m_street)
    {
        exit (EXIT_SUCCESS);
    }
    if (!m_street->indexOfObject(pSender) == UINT_MAX)
    {
        exit (EXIT_SUCCESS);
    }
    int indexOfLastSegment = m_street->indexOfObject(pSender);
    if (indexOfLastSegment == 0)
    {
        indexOfLastSegment = m_cMaxSegmentsNumber;
    }
    CCSprite* lastFragment = const_cast<CCSprite*>(
                static_cast<CCSprite*>(m_street->objectAtIndex(--indexOfLastSegment)));
    putFragmentBack(
        m_street->indexOfObject(pSender),
        lastFragment->getPositionY() + lastFragment->getContentSize().height);
}

void Terrain::setVelocity (const float &updateTo)
{
    if (updateTo != m_velocity)
    {
        if (updateTo > m_velocity)
        {
            m_player->acelerate();
        }
        if (updateTo > 0)
        {
            m_velocity = updateTo;
        }
        else
        {
           m_velocity = 0.1f;
        }
        m_player->setVelocity(m_velocity);
        aceleration ();
    }
}

void Terrain::putCar(Car* car)
{

    car->setPositionY(m_visibleSize.height + car->getContentSize().height);
    Car *correctedCarPosition = preventCollitionWitCars(car);
    if (!correctedCarPosition)
    {
        car->setFootpath(getNextFootPath(car->getFootpath()));
        correctedCarPosition = preventCollitionWitCars(car);
    }
    if (!correctedCarPosition)
    {
        car->setFootpath(getNextFootPath(car->getFootpath()));
        correctedCarPosition = preventCollitionWitCars(car);
    }

    if (correctedCarPosition)
    {
        putBody(correctedCarPosition,
            CCPoint(correctedCarPosition->getPositionX(),
                  m_visibleSize.height +
                      correctedCarPosition->getContentSize().height));
    }
    else
    {
        this->obstacleDone(car);
    }
}


const int Terrain::getNextFootPath(const int &currentFP) const
{
    switch (currentFP)
    {
    case Car::kLeft:
        return Car::kCenter;
        break;
    case Car::kCenter:
        return Car::kRigth;
        break;
    case Car::kRigth:
        return Car::kLeft;
        break;
    default:
        return Car::kCenter;
        break;
    }
}


Car* Terrain::preventCollitionWitCars(Car *car)
{
    CCObject *it = NULL;
    CCARRAY_FOREACH(m_cars, it)
    {
        if (!static_cast<Car*>(it)->isVisible() ||
            static_cast<Car*>(it)->getFootpath() != car->getFootpath())
        {
            continue;
        }
        Car *itc = static_cast<Car*>(it);
        if (!itc->isEqual(car) &&
            itc->getBaseForCollition().intersectsRect(car->getBaseForCollition()))
        {
            return NULL;
        }

        float t = ((itc->getPositionY() + itc->getContentSize().height*.5f) -
                   (car->getPositionY() - car->getContentSize().height*.5f)) /
                (itc->getVelocity() - car->getVelocity());
        if ((car->getPositionY() - car->getContentSize().height *.5) -
                ((m_velocity + car->getVelocity()) * t) > 0)
        {
            return NULL;
        }
    }

    return car;
}

void Terrain::putBody(Body* body, const CCPoint& from)
{
//TODO:
    body->stopAllActions();
    body->setPosition(from);

    CCSequence *seq = CCSequence::createWithTwoActions (
        CCMoveTo::create (
            getInterval (body->getPositionY(),
                         -body->getContentSize().height,
                         body->getVelocity()),
            CCPoint(body->getPositionX(), -body->getContentSize().height)),
        CCCallFuncN::create (this, callfuncN_selector(Terrain::obstacleDone)));
    body->runAction (seq);
}



void Terrain::putObstacle ()
{
    if (m_obstaclesIdle > 0)
    {
        Obstacle* obstacle =
                static_cast<Obstacle*>(getAndActiveRandomBody(m_obstaclesIdle--,
                                                              m_obstacles));
        if (m_gc->getRandomIntegerInRange(0, 2))//left or rigth
        {
            obstacle->setFootpath(Body::kRigth);
                obstacle->setPositionX(obstacle->getPositionX() +
                                       obstacle->getContentSize().width*.2f);
        }
        else
        {
            obstacle->setFootpath(Body::kLeft);
                obstacle->setPositionX(obstacle->getPositionX() -
                                       obstacle->getContentSize().width*.2f);
        }
        this->putBody(obstacle, CCPoint(obstacle->getPositionX(),
                                      m_visibleSize.height +
                                      obstacle->getContentSize().height*.5f));
    }
}

void Terrain::putTree()
{
    if (m_treesIdle > 0)
    {
        Tree *obstacle =
                static_cast<Tree*>(getAndActiveRandomBody(m_treesIdle--,
                                                              m_trees));
        if (m_gc->getRandomIntegerInRange(0, 2))//left or rigth
        {
            obstacle->setToLeft();
        }
        else
        {
            obstacle->setToRigth();
        }
        this->putBody(obstacle, CCPoint(obstacle->getPositionX(),
                                     m_visibleSize.height +
                                        obstacle->getContentSize().height*.5f));
    }
}

Body* Terrain::getAndActiveRandomBody(int bodiesIdle, CCArray *bodyList)
{
    int ignores = m_gc->getRandomIntegerInRange (0, bodiesIdle);
    Body* pBodyRet = NULL;
    for (int i = 0; ignores >= 0; i++)
    {
        pBodyRet = static_cast<Body*>(bodyList->objectAtIndex(i));
        if (!pBodyRet->isVisible())
        {
            ignores--;
        }
    }
    pBodyRet->setVisible (true);
    pBodyRet->setActive(true);
    return pBodyRet;
}

Car* Terrain::getAndActiveRandomCar()
{
    Car *pRet = NULL;
    if (m_carsIdle > 0)
    {
        pRet = static_cast<Car*>(getAndActiveRandomBody(m_carsIdle--, m_cars));
    }
    return pRet;
}


void Terrain::obstacleDone(CCObject *pSender)
{
    switch (static_cast<Body*>(pSender)->getKind())
    {
    case Body::kTree:
        ++m_treesIdle;
        static_cast<Body*>(pSender)->setVisible(false);
        static_cast<Body*>(pSender)->setActive(false);
        break;
    case Body::kGomas:
    case Body::kAceite:
    case Body::kBasurero:
        ++m_obstaclesIdle;
        static_cast<Body*>(pSender)->setVisible (false);
        static_cast<Body*>(pSender)->setActive(false);
        break;
    case Body::kCar:
        ++m_carsIdle;
        static_cast<Body*>(pSender)->setVisible (false);
        static_cast<Body*>(pSender)->setActive(false);
        break;
    default:
        break;
    }
}

const float Terrain::getVelocity() const
{
    return m_velocity;
}

const Player* Terrain::getPlayer() const
{
    return m_player;
}

void Terrain::changeFootpathTo (int changeTo)
{
    m_player->setFootpath(changeTo);
}

void Terrain::changeFootpathToLeft (int scales)
{

}

void Terrain::changeFootpathToRigth (int scales)
{

}


void Terrain::aceleration ()
{
    for (int i = 0; i < m_cMaxSegmentsNumber; i++)
    {
        putFragmentBack (
            i,
            static_cast<CCSprite*>(m_street->objectAtIndex(i))->getPositionY());
    }

    CCObject *it = NULL;
    CCARRAY_FOREACH (m_trees, it)
    {
        if (static_cast<Tree*>(it)->isVisible())
        {
            putBody(static_cast<Obstacle*>(it),
                    static_cast<Obstacle*>(it)->getPosition());
        }
    }

    CCARRAY_FOREACH (m_cars, it)
    {
        if (static_cast<Obstacle*>(it)->isVisible())
        {
            putBody(static_cast<Obstacle*>(it),
                    static_cast<Obstacle*>(it)->getPosition());
        }
    }

    CCARRAY_FOREACH (m_obstacles, it)
    {
        if (static_cast<Obstacle*>(it)->isVisible())
        {
            putBody(static_cast<Obstacle*>(it),
                    static_cast<Obstacle*>(it)->getPosition());
        }
    }
}

const CCArray *Terrain::getStreet() const
{
    return m_street;
}

const CCArray *Terrain::getPatchs() const
{
    return m_patchs;
}

const CCArray* Terrain::getTrees() const
{
    return m_trees;
}

const CCArray *Terrain::getObstacles() const
{
    return m_obstacles;
}

const CCArray* Terrain::getCars() const
{
    return m_cars;
}


Terrain::GameStatus Terrain::update()
{
    //FIXME: m_player->update();

    CCRect playerRect = m_player->getBaseForCollition();
    CCObject *it = NULL;
    CCARRAY_FOREACH (m_obstacles, it)
    {
        std::map<Collition, bool>::iterator index =
                m_mapObstaclesPlayerCollitions.find(Collition(m_player, it));
        if (index->second == true)
        {
            index->second = static_cast<Obstacle*>(it)->
                    getBaseForCollition().intersectsRect(playerRect);
        }
        else
        {
            if (static_cast<Obstacle*>(it)->
                    getBaseForCollition().intersectsRect(playerRect))
            {
                //CC_AUDIO->playEffect("SOUND/backfire.wav");
                static_cast<Obstacle*>(it)->crash(m_player);
                static_cast<Obstacle*>(it)->setActive (false);
                index->second = true;
                return kCollided;
            }
        }
    }

    CCARRAY_FOREACH (m_cars, it)
    {
        std::map<Collition, bool>::iterator index =
                m_mapCarsPlayerCollitions.find(Collition(m_player, it));
        if (index->second == true)
        {
            index->second = static_cast<Obstacle*>(it)->
                    getBaseForCollition().intersectsRect(playerRect);
        }
        else
        {
            if (static_cast<Obstacle*>(it)->
                    getBaseForCollition().intersectsRect(playerRect))
            {
                //CC_AUDIO->playEffect("SOUND/skid.wav");
                static_cast<Obstacle*>(it)->setActive (false);
                m_player->crash(static_cast<Car*>(it));
                index->second = true;
                return kGameOver;
            }
        }
    }

    CCObject *itCars = NULL;
    CCARRAY_FOREACH(m_cars, itCars)
    {
        CCObject *itObstacles = NULL;
        CCARRAY_FOREACH(m_obstacles, itObstacles)
        {
            std::map<Collition, bool>::iterator index =
                    m_mapCarsObstaclesCollitions.find(Collition(itCars, itObstacles));
            if (index->second == true)
            {
                index->second = static_cast<Body*>(itCars)->
                        getBaseForCollition().intersectsRect(
                            static_cast<Body*>(itObstacles)->getBaseForCollition());
            }
            else
            {
                if (static_cast<Body*>(itCars)->
                        getBaseForCollition().intersectsRect(
                            static_cast<Body*>(itObstacles)->getBaseForCollition()))
                {
                    //CC_AUDIO->playEffect("SOUND/skid_tyres.wav");
                    index->second = true;
                    static_cast<Obstacle*>(itObstacles)->crash(static_cast<Car*>(itCars));
                }
            }
        }
    }

    return kPlaying;
}

void Terrain::pauseTerrain()
{
    CCActionManager* actionManager = CCDirector::sharedDirector()->getActionManager();
    actionManager->pauseTarget(m_player);
    CCObject *iter = NULL;
    CCARRAY_FOREACH(m_cars, iter)
    {
        actionManager->pauseTarget(iter);
    }
    CCARRAY_FOREACH(m_trees, iter)
    {
        actionManager->pauseTarget(iter);
    }
    CCARRAY_FOREACH(m_obstacles, iter)
    {
        actionManager->pauseTarget(iter);
    }
    CCARRAY_FOREACH(m_street, iter)
    {
        actionManager->pauseTarget(iter);
    }
    CCARRAY_FOREACH(m_patchs, iter)
    {
        actionManager->pauseTarget(iter);
    }
}

void Terrain::stopTerrain()
{
    m_player->stopAllActions();
    CCObject *iter = NULL;
    CCARRAY_FOREACH(m_cars, iter)
    {
        static_cast<CCSprite*>(iter)->stopAllActions();
    }
    CCARRAY_FOREACH(m_trees, iter)
    {
        static_cast<CCSprite*>(iter)->stopAllActions();
    }
    CCARRAY_FOREACH(m_obstacles, iter)
    {
        static_cast<CCSprite*>(iter)->stopAllActions();
    }
    CCARRAY_FOREACH(m_street, iter)
    {
        static_cast<CCSprite*>(iter)->stopAllActions();
    }
    CCARRAY_FOREACH(m_patchs, iter)
    {
        static_cast<CCSprite*>(iter)->stopAllActions();
    }
}

void Terrain::resumeTerrain()
{
    CCActionManager* actionManager = CCDirector::sharedDirector()->getActionManager();
    CCObject *iter = NULL;

    CCARRAY_FOREACH(m_patchs, iter)
    {
        actionManager->resumeTarget(iter);
    }
    CCARRAY_FOREACH(m_street, iter)
    {
        actionManager->resumeTarget(iter);
    }
    CCARRAY_FOREACH(m_obstacles, iter)
    {
        actionManager->resumeTarget(iter);
    }
    CCARRAY_FOREACH(m_trees, iter)
    {
        actionManager->resumeTarget(iter);
    }
    CCARRAY_FOREACH(m_cars, iter)
    {
        actionManager->resumeTarget(iter);
    }
    actionManager->resumeTarget(m_player);
}
