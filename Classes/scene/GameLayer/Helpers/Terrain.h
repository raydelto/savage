/*! \file Terrain.h
    \author <denisacostaq\@gmail.com>
    \date Sat Feb  8 00:51:59 CST 2014

    \brief This file become from: src/portable/scene/GameLayer/Helpers/Terrain.h

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

#ifndef TERRAIN_H
#define TERRAIN_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "scene/GameLayer/Bodys/Obstacle.h"
#include "scene/GameLayer/Bodys/Tree.h"
#include "scene/GameLayer/Bodys/Player.h"
#include "scene/GameLayer/Bodys/CarWithPerspective.h"
#include "GlobalColaboration.h"
#include "scene/GameLayer/Helpers/Collition.h"

#include <map>

USING_NS_CC;

/*!
 * \brief The Terrain class esta herencia rompe con la arquitectura
 * \brief pero se necesita para CCCallFuncN::create (this, callfuncN_selector(Terrain::repositioneTerrain)));
 * \brief ,en las versiones actuales de coco no hace falta
 */
class Terrain : public CCLayer
{
public:
    ~Terrain();

//    Terrain(const Terrain&) = delete;
//    Terrain& operator=(const Terrain&) = delete;
//    Terrain(const Terrain&&) = delete;
//    Terrain& operator=(const Terrain&&) = delete;

    enum Level{kLevel_1, kLevel_2, kLevel_3, kLevel_4, kLevel_5};
    /*!
     * \warning create this is not an autorelease CCObject
     * \return
     */
    static Terrain* create(const PlayerKind &selectedPlayer,
                           const Level& selectedLevel);
    const CCArray *getStreet() const;
    const CCArray *getPatchs() const;
    const CCArray *getTrees() const;
    const CCArray *getObstacles() const;
    const CCArray* getCars() const;
    const Player *getPlayer() const;

    void setVelocity(const float &updateTo);
    const float getVelocity() const;


    void changeFootpathTo(int changeTo);
    void putCar(Car *car);

    /*!
     * \brief putObstacle importante hacer m_obstaclesIdle-- solo despues
     * \brief de llamar a getAndActiveRandomBody ;)
     * \sa putTree(), getAndActiveRandomCar()
     */
    void putObstacle();

    /*!
     * \brief getAndActiveRandomCar importante hacer m_carsIdle-- solo despues
     * \brief de llamar a getAndActiveRandomBody ;)
     * \return un carro para chocar o null si no hay ninguno disponible
     * \sa putObstacle(), putTree()
     */
    Car *getAndActiveRandomCar();

    /*!
     * \brief putTree importante hacer m_treesIdle-- solo despues
     * \brief de llamar a getAndActiveRandomBody ;)
     * \sa putObstacle(), getAndActiveRandomCar()
     */
    void putTree();

    /*!
     * \brief The GameStatus enum
     */
    enum GameStatus {kPlaying, kCollided, kGameOver};

    /*!
     * \brief update
     * \return
     */
    GameStatus update();

    void pauseTerrain();

    void stopTerrain();

    void resumeTerrain();

private:
    explicit Terrain(const PlayerKind &selectedPlayer, const Level &selectedLevel);

    bool init();
    void initMembers();
    void initStreet();
    void initTrees();
    void initObstacles();
    void initCars();
    void initPlayer();



    void putFragmentBack(int fragmentIndex, float fromY);
    void repositioneTerrain (CCObject *pSender);
    float getInterval (const float &begin, const float &end, float selfVelocity);

    void aceleration ();

    Body *getAndActiveRandomBody(int bodiesIdle, CCArray *bodyList);
    void putBody(Body* body, const CCPoint &from);
    void obstacleDone(CCObject *pSender);
    const int getNextFootPath(const int& currentFP) const;

    void changeFootpathToLeft (int scales);

    void changeFootpathToRigth (int scales);

    /*!
     * \brief preventCollitionWitCars
     * \brief The distance between \f$(x_1,y_1)\f$ and \f$(x_2,y_2)\f$ is \f$\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}\f$.
     * \param car
     * \return
     */
    Car *preventCollitionWitCars(Car *car);

    CCSize m_visibleSize;
    CCArray *m_street;
    CCArray *m_patchs;

    const short m_cMaxSegmentsNumber;//{3};

    float m_velocity;

    std::vector<CCPoint> m_footpathPoints;

    Player *m_player;

    Level m_selectedLevel;
    CCArray *m_trees;
    CCArray *m_obstacles;

    short m_treesIdle;
    short m_obstaclesIdle;
    short m_carsIdle;
    GlobalColaboration *m_gc;


    CCArray *m_cars;

    PlayerKind m_selectedPlayer;

    std::map<Collition, bool> m_mapObstaclesPlayerCollitions;
    std::map<Collition, bool> m_mapCarsPlayerCollitions;
    std::map<Collition, bool> m_mapCarsObstaclesCollitions;
};

#endif // TERRAIN_H
