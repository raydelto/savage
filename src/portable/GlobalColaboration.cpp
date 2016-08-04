/*! \file GlobalColaboration.cpp
    \author <denisacostaq\@gmail.com>
    \date Fri Feb  7 19:15:57 CST 2014

    \brief This file become from: src/portable/GlobalColaboration.cpp

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

#include "GlobalColaboration.h"

GlobalColaboration* GlobalColaboration::m_selfInstance {nullptr};

/*! FIXME...
 * \brief GlobalColaboration::GlobalColaboration hacerele un destructor que
 * \brief funcione a la salida del programa.
 */
GlobalColaboration::GlobalColaboration()
    : m_bgMusicVolume {userDefaultData.bgMusicVolumeDefalutValue}
    , m_efMusicVolume {userDefaultData.efMusicVolumeDefalutValue}
    , m_audioEnabled {userDefaultData.audioEnabled}
    , m_avaliablesLevels {userDefaultData.avaliablesLevelsDefalutValue}
{
    srand(time(nullptr));

    //LOAD CONFIGURATION FROM XML
    loadBgMusicVolume();
    loadEfMusicVolume();
    loadAudioEnabled();
    loadAvaliablesLevels();
}

GlobalColaboration *GlobalColaboration::getInstance()
{
    if (!m_selfInstance)
    {
        m_selfInstance = new GlobalColaboration();
    }

    return m_selfInstance;
}


GlobalColaboration::~GlobalColaboration()
{
}


void GlobalColaboration::loadBgMusicVolume()
{
    if (CCUserDefault::sharedUserDefault()->isXMLFileExist ())
    {
        m_bgMusicVolume =  CCUserDefault::sharedUserDefault()->getFloatForKey(
                    userDefaultData.bgMusicVolume,
                    userDefaultData.bgMusicVolumeDefalutValue);
    }
    else
    {
        m_bgMusicVolume = userDefaultData.bgMusicVolumeDefalutValue;
    }
}

void GlobalColaboration::loadEfMusicVolume()
{
    if (CCUserDefault::sharedUserDefault()->isXMLFileExist ())
    {
        m_efMusicVolume = CCUserDefault::sharedUserDefault()->getFloatForKey(
                    userDefaultData.efMusicVolume,
                    userDefaultData.efMusicVolumeDefalutValue);
    }
    else
    {
        m_efMusicVolume = userDefaultData.efMusicVolumeDefalutValue;
    }
}

void GlobalColaboration::loadAudioEnabled()
{
    if (CCUserDefault::sharedUserDefault()->isXMLFileExist())
    {
        m_audioEnabled = CCUserDefault::sharedUserDefault()->getBoolForKey(
                    userDefaultData.audioEnabled,
                    userDefaultData.audioEnabledDefalutValue);
    }
    else
    {
        m_audioEnabled = userDefaultData.audioEnabledDefalutValue;
    }
}

void GlobalColaboration::loadAvaliablesLevels()
{
    if (CCUserDefault::sharedUserDefault()->isXMLFileExist())
    {
        m_avaliablesLevels = CCUserDefault::sharedUserDefault()->getIntegerForKey(
                    userDefaultData.avaliablesLevels,
                    userDefaultData.avaliablesLevelsDefalutValue);
    }
    else
    {
        m_avaliablesLevels = userDefaultData.avaliablesLevelsDefalutValue;
    }
}

const float GlobalColaboration::getInterval(const float &begin,
                                            const float &end,
                                            const float &velocity) const
{
    float interval = (begin - end)/velocity;
    if (interval < 0)
    {
        interval *= -1;
    }
    return interval/(4/CCDirector::sharedDirector()->getContentScaleFactor());
}
