EXECUTABLE = SavageRace

COCOS_ROOT = ../../..

INCLUDES = -I.. \
          -I../Classes \
          -I$(COCOS_ROOT)/CocosDenshion/include

#CXXFLAGS += -std=c++11
CXXFLAGS += -g
CFLAGS += -g

SOURCES = main.cpp \
          ../Classes/AppDelegate.cpp \
          ../Classes/scene/MainMenu/MenuLayer.cpp \
          ../Classes/scene/MainMenu/CreditsLayer.cpp \
          ../Classes/scene/MainMenu/PlayerSelection.cpp \
          ../Classes/scene/MainMenu/LevelSelection.cpp \
          ../Classes/scene/GameLayer/L4GameLayer.cpp \
          ../Classes/scene/GameLayer/L1GameLayer.cpp \
          ../Classes/scene/GameLayer/GameLayer.cpp \
          ../Classes/scene/GameLayer/Helpers/Terrain.cpp \
          ../Classes/scene/GameLayer/Helpers/Collition.cpp \
          ../Classes/scene/GameLayer/L3GameLayer.cpp \
          ../Classes/scene/GameLayer/L2GameLayer.cpp \
          ../Classes/scene/GameLayer/L5GameLayer.cpp \
          ../Classes/scene/GameLayer/Bodys/Player.cpp \
          ../Classes/scene/GameLayer/Bodys/CarWithPerspective.cpp \
          ../Classes/scene/GameLayer/Bodys/Car.cpp \
          ../Classes/scene/GameLayer/Bodys/Obstacle.cpp \
          ../Classes/scene/GameLayer/Bodys/Tree.cpp \
          ../Classes/scene/GameLayer/Bodys/Body.cpp \
          ../Classes/GlobalColaboration.cpp

include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d -lcocosdenshion
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
