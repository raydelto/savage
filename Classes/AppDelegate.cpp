/*! \file AppDelegate.cpp
    \author <denisacostaq\@gmail.com>
    \date Fri Feb  7 19:12:07 CST 2014

    \brief This file become from: src/portable/AppDelegate.cpp

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


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector *pDirector = CC_DIRECTOR;

    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView (pEGLView);
    CCSize frameSize = pEGLView->getFrameSize();

    if (MIN(frameSize.width, frameSize.height) < 400 || true)//379
    {
        pDirector->setContentScaleFactor(
            MIN(mediumResource.size.height/
                    CCEGLView::sharedOpenGLView()->getFrameSize().height,
                mediumResource.size.width/
                    CCEGLView::sharedOpenGLView()->getFrameSize().width));
        std::vector<std::string> paths;
        paths.push_back(mediumResource.directory);
        paths.push_back("Sounds/");
        CCFileUtils::sharedFileUtils()->setSearchPaths (paths);
    }
    else if (MIN(frameSize.width, frameSize.height) < 800)//768
    {
        pDirector->setContentScaleFactor(
            MIN(mediumResource.size.height/
                    CCEGLView::sharedOpenGLView()->getFrameSize().height,
                mediumResource.size.width/
                    CCEGLView::sharedOpenGLView()->getFrameSize().width));
        std::vector<std::string> paths;
        paths.push_back(mediumResource.directory);
        paths.push_back("Sounds/");
        CCFileUtils::sharedFileUtils()->setSearchPaths (paths);
    }
    else if (MIN(frameSize.width, frameSize.height) < 1200)//1080
    {
        pDirector->setContentScaleFactor(
            MIN(mediumResource.size.height/
                    CCEGLView::sharedOpenGLView()->getFrameSize().height,
                mediumResource.size.width/
                    CCEGLView::sharedOpenGLView()->getFrameSize().width));
        std::vector<std::string> paths;
        paths.push_back(mediumResource.directory);
        paths.push_back("Sounds/");
        CCFileUtils::sharedFileUtils()->setSearchPaths (paths);
    }

    // turn on display FPS
    pDirector->setDisplayStats (false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // CCScene: it's an autorelease CCObject
    CCScene *mainMenuScene = MainMenu::MenuLayer::scene();
    if (mainMenuScene)
    {
        pDirector->runWithScene (mainMenuScene);
        return true;
    }
    {
        return false;
    }
}

void AppDelegate::applicationDidEnterBackground()
{
    CC_DIRECTOR->stopAnimation();
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground()
{
    CC_DIRECTOR->startAnimation();
///CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
