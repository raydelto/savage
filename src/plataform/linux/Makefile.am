if DEBUG
COCOS_LIB_PATH=$(COCOS2DX_ROOT)@PLATAFORM_LIBS_PATH@/debug
else
COCOS_LIB_PATH=$(COCOS2DX_ROOT)@PLATAFORM_LIBS_PATH@/release
endif

AUTOMAKE_OPTIONS = subdir-objects
CC_FLAGS = -MMD -Wall -fPIC
AM_CPPFLAGS = -MMD -Wall -fPIC -D @PLATAFORM@ -std=c++11 -Werror

AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/include
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/kazmath/include
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/platform

AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/external

AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/extensions

AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/CocosDenshion/include

#AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/extensions

#this are plataform depends
AM_CPPFLAGS += -I $(COCOS2DX_ROOT)/cocos2dx/platform/linux

AM_CPPFLAGS += -I @top_builddir@/src/portable

bin_PROGRAMS = savage_race


#@top_builddir@/doc/MainPage.h

HEADERSSSS = \
		@top_builddir@/src/portable/AppDelegate.h \
		@top_builddir@/src/portable/AppMacros.h \
        @top_builddir@/src/portable/GlobalColaboration.h \
        @top_builddir@/src/portable/scene/MainMenu/MenuLayer.h \
        @top_builddir@/src/portable/scene/MainMenu/CreditsLayer.h \
        @top_builddir@/src/portable/scene/MainMenu/LevelSelection.h \
        @top_builddir@/src/portable/scene/MainMenu/PlayerSelection.h \
        @top_builddir@/src/portable/scene/GameLayer/GameLayer.h \
        @top_builddir@/src/portable/scene/GameLayer/L1GameLayer.h \
        @top_builddir@/src/portable/scene/GameLayer/L2GameLayer.h \
        @top_builddir@/src/portable/scene/GameLayer/L3GameLayer.h \
        @top_builddir@/src/portable/scene/GameLayer/L4GameLayer.h \
        @top_builddir@/src/portable/scene/GameLayer/L5GameLayer.h \
        @top_builddir@/src/portable/scene/GameLayer/Helpers/Terrain.h \
        @top_builddir@/src/portable/scene/GameLayer/Helpers/Collition.h \
        @top_builddir@/src/portable/scene/GameLayer/Bodys/Body.h \
        @top_builddir@/src/portable/scene/GameLayer/Bodys/Car.h \
        @top_builddir@/src/portable/scene/GameLayer/Bodys/CarWithPerspective.h \
        @top_builddir@/src/portable/scene/GameLayer/Bodys/Tree.h \
        @top_builddir@/src/portable/scene/GameLayer/Bodys/Obstacle.h \
        @top_builddir@/src/portable/scene/GameLayer/Bodys/Player.h


savage_race_SOURCES = \
		@top_builddir@/src/plataform/linux/main.cpp \
		@top_builddir@/src/portable/AppDelegate.cpp \
        @top_builddir@/src/portable/GlobalColaboration.cpp \
        @top_builddir@/src/portable/scene/MainMenu/MenuLayer.cpp \
        @top_builddir@/src/portable/scene/MainMenu/CreditsLayer.cpp \
        @top_builddir@/src/portable/scene/MainMenu/LevelSelection.cpp \
        @top_builddir@/src/portable/scene/MainMenu/PlayerSelection.cpp \
        @top_builddir@/src/portable/scene/GameLayer/GameLayer.cpp \
        @top_builddir@/src/portable/scene/GameLayer/L1GameLayer.cpp \
        @top_builddir@/src/portable/scene/GameLayer/L2GameLayer.cpp \
        @top_builddir@/src/portable/scene/GameLayer/L3GameLayer.cpp \
        @top_builddir@/src/portable/scene/GameLayer/L4GameLayer.cpp \
        @top_builddir@/src/portable/scene/GameLayer/L5GameLayer.cpp \
        @top_builddir@/src/portable/scene/GameLayer/Helpers/Terrain.cpp \
        @top_builddir@/src/portable/scene/GameLayer/Helpers/Collition.cpp \
        @top_builddir@/src/portable/scene/GameLayer/Bodys/Body.cpp \
        @top_builddir@/src/portable/scene/GameLayer/Bodys/Car.cpp \
        @top_builddir@/src/portable/scene/GameLayer/Bodys/CarWithPerspective.cpp \
        @top_builddir@/src/portable/scene/GameLayer/Bodys/Tree.cpp \
        @top_builddir@/src/portable/scene/GameLayer/Bodys/Obstacle.cpp \
        @top_builddir@/src/portable/scene/GameLayer/Bodys/Player.cpp \
        $(HEADERSSSS)









#esto da problema porque pasa "vacio"
#CCApplication.h: No such file or directory
#asi que hay que comentarlo
#ninno_CPPFLAGS = @GLS_CFLAGS@
savage_race_LDFLAGS =  @GLS_LIBS@

savage_race_LDADD = \
        $(COCOS_LIB_PATH)/libcocos2d.so \
        $(COCOS_LIB_PATH)/libcocosdenshion.so
