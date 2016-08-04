/*! \file GameLayer.h
    \author <denisacostaq\@gmail.com>
    \date Fri Feb  7 18:33:16 CST 2014

    \brief This file become from: src/portable/scene/GameLayer.h

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

#ifndef GAMELAYER_H
#define GAMELAYER_H

#include "Helpers/Terrain.h"
#include "AppMacros.h"
#include "cocos2d.h"
USING_NS_CC;

class GameLayer : public CCLayer
{
public:

    //disable copy and move
//    GameLayer(const GameLayer&) = delete;
//    GameLayer& operator= (const GameLayer&) = delete;
//    GameLayer(const GameLayer&&) = delete;
//    GameLayer& operator= (const GameLayer&&) = delete;
    ~GameLayer();

//    //WARNING: see doxygen doc
//    /*! \warning no implemente este metodo a menos que sepa lo que esta haciendo.
//     * \brief create no haga este metedo ya que la jerarquia de clases
//     * \brief garantiza que se reserve memoria desde el hijo mediante el
//     * \brief constructor
//     * \return
//     */
//    static GameLayer* create() = delete;

    virtual bool init();

    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);

protected:
    GameLayer();

    virtual void initGame() = 0;

    void putObstacle(float dt);
    void putCar(float dt);
    void putTree(float dt);
    virtual void update(float dt);

    CCSize m_visibleSize;
    CCPoint m_visibleOrigin;
    Terrain *m_terrain;
    const short m_cTimerValue;// {60};
    short m_timmer;
    CCLabelTTF *m_timmerLabel;
    Terrain::GameStatus m_gameStatus;

    short m_currentLevel;

private:
    void goToPlay();

    void initMembers();

    void initMenu();

    void updateTimmer();

    void win();

    void pauseGame();
    void resumeGame();

    void menuPauseCallback();
    void menuResumeCallback();
    void menuExitCallback();

    void stopGame();

    void updateexplosioPosition(float dt);
    void gameOver();

    CCPoint m_pointOfTouchBegan;

    bool m_movinTouch;


    CCSprite *m_goToPlay;
    CCSprite *m_wine;
    CCSprite *m_fail;

    CCMenu *m_menu;

    CCMenu *m_pMenuOnPause;

    CCAnimation *m_animImpact;
    CCSprite *m_Exp0020;
};

#endif // GAMELAYER_H
