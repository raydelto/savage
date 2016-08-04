/*! \file AppDelegate.h
    \author <denisacostaq\@gmail.com>
    \date Fri Feb  7 19:12:07 CST 2014

    \brief This file become from: src/portable/AppDelegate.h

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

#ifndef APPDELEGATE_H
#define APPDELEGATE_H

#include "scene/MainMenu/MenuLayer.h"
#include "AppMacros.h"
#include <string>

USING_NS_CC;

class AppDelegate : public cocos2d::CCApplication
{
public:
    AppDelegate();

    //NOTE: disable copy and move
    AppDelegate(const AppDelegate&) = delete;
    AppDelegate& operator=(const AppDelegate&) = delete;
    AppDelegate(const AppDelegate&&) = delete;
    AppDelegate& operator=(const AppDelegate&&)=delete;

    ~AppDelegate ();

    /*! Implement CCDirector and CCScene init code here.
	\brief Here is the place for you.
    \return true    Initialize success, app continue.
    \return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /*! The function be called when the application enter background
    \param  the CCPointer of the application
    */
    virtual void applicationDidEnterBackground();

    /*! The function be called when the application enter foreground
    \param  the CCPointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // APPDELEGATE_H
