/*! \file GlobalColaboration.h
    \author <denisacostaq\@gmail.com>
    \date Fri Feb  7 19:15:57 CST 2014

    \brief This file become from: src/portable/GlobalColaboration.h

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

#ifndef GlobalColaboration_H
#define GlobalColaboration_H

#include "AppMacros.h"

USING_NS_CC;
class GlobalColaboration
{

public:
    //NOTE: disable copy and move
    //GlobalColaboration(const GlobalColaboration&) = delete;
    //GlobalColaboration& operator=(const GlobalColaboration&) = delete;
    //GlobalColaboration(const GlobalColaboration&&) = delete;
    //GlobalColaboration& operator=(const GlobalColaboration&&) = delete;


    static GlobalColaboration *getInstance();

    /*! \brief Retorna un numero aleatorio en en el rango especificado.
     * \brief getRandomIntegerInRange le valo incluye... TODO
     * \param min valor minimo en el rango
     * \param max valor maximo en el rango
     * \return rand (rand < max && rand >= min).
     * \sa rand, srand
     */
    inline int getRandomIntegerInRange (int min, int max) const
    {
        return (rand() % (max - min)) + min;
    }

    inline const float& getBgMusicVolume() const
    {
        return m_bgMusicVolume;
    }
    inline const float& getEfMusicVolume() const
    {
        return m_efMusicVolume;
    }

    inline const bool& isAudioEnabled() const
    {
        return m_audioEnabled;
    }

    inline const short& getAvaliablesLevels()
    {
        return m_avaliablesLevels;
    }

    inline void setBgMusicVolume(const float &val)
    {
        if (CCUserDefault::sharedUserDefault()->isXMLFileExist ())
        {
            CCUserDefault::sharedUserDefault()->setFloatForKey(
                        userDefaultData.bgMusicVolume, (m_bgMusicVolume = val));
        }
    }

    inline void setEfMusicVolume(const float &val)
    {
        if (CCUserDefault::sharedUserDefault()->isXMLFileExist ())
        {
            CCUserDefault::sharedUserDefault()->setFloatForKey(
                        userDefaultData.efMusicVolume, (m_efMusicVolume = val));
        }
    }

    inline void setAudioEnabled (const bool& val)
    {
        if (CCUserDefault::sharedUserDefault()->isXMLFileExist ())
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey(
                        userDefaultData.audioEnabled, (m_audioEnabled = val));
        }
    }

    inline void setAvaliablesLevels(const short &val)
    {
        if (CCUserDefault::sharedUserDefault()->isXMLFileExist())
        {
            CCUserDefault::sharedUserDefault()->setIntegerForKey(
                        userDefaultData.avaliablesLevels, (m_avaliablesLevels = val));
        }
    }

    /*! \brief retorna un intervalo positivo.
     * \brief getInterval retorna un intervalo positivo
     * \param begin punto inicial
     * \param end punto final
     * \param velocity velocidad a la que se movera entre los puntos
     * \warning no pase cero en la velocidad
     * \return el intervalo para moverse entre los puntos a la velocidad dada.
     */
    const float getInterval(const float &begin,
                            const float &end,
                            const float &velocity) const;

private:

    /*! \brief singletlon
     * \brief m_selfInstance instancia de la clase, implementa un singletlon
     */
    static GlobalColaboration* m_selfInstance;

    GlobalColaboration();

    /*!
     * \brief GlobalColaboration::~GlobalColaboration es privado, nunca elimine la
     * \brief instancia en una clase que la haya obtenido a travez de getInstance()
     * \sa getInstance ();
     */
    ~GlobalColaboration ();

    void loadBgMusicVolume();
    void loadEfMusicVolume();
    void loadAudioEnabled();
    void loadAvaliablesLevels();

    struct UserDefaultData {
      UserDefaultData()
        : bgMusicVolume ("bgMusicVolume")
        , bgMusicVolumeDefalutValue(0.6f)
        , efMusicVolume("efMusicVolume")
        , efMusicVolumeDefalutValue(0.4f)
        , audioEnabled ("audioEnabled")
        , audioEnabledDefalutValue (true)
        , avaliablesLevels("avaliablesLevels")
        , avaliablesLevelsDefalutValue(1) {
      }
      const char *bgMusicVolume;
      float bgMusicVolumeDefalutValue;
      const char *efMusicVolume;
      float efMusicVolumeDefalutValue;
      const char *audioEnabled;
      bool audioEnabledDefalutValue;
      const char *avaliablesLevels;
      short avaliablesLevelsDefalutValue;
    };
    UserDefaultData userDefaultData;
    float m_bgMusicVolume;
    float m_efMusicVolume;
    bool m_audioEnabled;
    short m_avaliablesLevels;
};

#endif // GlobalColaboration_H
