//
//  LuaGameActorScript.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/19/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__LuaGameActorScript__
#define __LuaProject__LuaGameActorScript__

#include <iostream>

/* Lua */
#include <lua.hpp>

#include "GameActor.h"

class LuaGameActorScript {
    
public:
    LuaGameActorScript();
    
public:
    GameActor *createNewGameActor(lua_State *lua);
    
    void onError(int errorCode);
    
    bool onCollide(GameActor &other);
    bool onSight(GameActor &other);
    bool onTargetUpdate(GameActor &other);
    
    void onKeyboard();
    
private:
    void setEnvironmentFor(lua_State *lua, GameActor &actor);
    bool initializeActor(lua_State *lua, GameActor &actor);
    
};

#endif /* defined(__LuaProject__LuaGameActorScript__) */
