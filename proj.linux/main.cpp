/*! \file main.cpp
    \author <denisacostaq\@gmail.com>
    \date Fri Feb  7 19:11:57 CST 2014

    \brief This file become from: src/plataform/linux/main.cpp

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

#include "AppDelegate.h"

#include <cstdio>

/*! You can use the command line for especific resolution.
	\brief The default value is same as denisacostaq parameter
*/
int main(int argc, char **argv)
{
    // create the application instance
    AppDelegate app;

    CCEGLView* CCEGLView = CCEGLView::sharedOpenGLView();
    CCEGLView->setFrameSize(1080/4, 1920/4);
    //CCEGLView->setFrameSize(270, 480);

    return CCApplication::sharedApplication()->run();
}
