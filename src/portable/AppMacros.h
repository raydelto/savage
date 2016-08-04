/*! \file AppMacros.h
    \author <denisacostaq\@gmail.com>
    \date Fri Feb  7 19:12:46 CST 2014

    \brief This file become from: src/portable/AppMacros.h
    \brief This file rename some frequentile methods as macros, and too include
    \brief \"ccMacros.h\" from cocos2dx    

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


#ifndef _APPMACROS_H
#define _APPMACROS_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

typedef struct tagResource
{
    cocos2d::CCSize size;
    std::string directory;
}
Resource;


static Resource mediumResource  =  { cocos2d::CCSize(1080, 1920),   "IMG/1920x1080" };


enum class zOrder
{
    zIndex_0 = 0,
    zIndex_1,
    zIndex_2,
    zIndex_3,
    zIndex_4,
    zIndex_5,
    zIndex_6
};

/*!
 * \brief The PlayerKind enum es el tipo de carro que se selecciona desde la
 * \brief ecena encargada.
 */
enum class PlayerKind
{
    kPlayer_1, /**< seria el mas lento actualmente conocido como Auto-Azul.png*/
    kPlayer_2, /**< seria el medio lento actualmente conocido como Auto-Amarillo.png*/
    kPlayer_3 /**< seria el mas rapido lento actualmente conocido como Auto-Rojo.png*/
};

typedef struct UserDefaultData
{
    const char *bgMusicVolume {"bgMusicVolume"};
    const float bgMusicVolumeDefalutValue {0.6f};
    const char *efMusicVolume {"efMusicVolume"};
    const float efMusicVolumeDefalutValue {0.4f};
    const char *audioEnabled {"audioEnabled"};
    const bool audioEnabledDefalutValue {true};
    const char *avaliablesLevels {"avaliablesLevels"};
    const short avaliablesLevelsDefalutValue {1};
}
UserDefaultData;

const UserDefaultData userDefaultData;

#define CC_DIRECTOR cocos2d::CCDirector::sharedDirector()
#define CC_AUDIO CocosDenshion::SimpleAudioEngine::sharedEngine()

#endif
