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

#include "GameActorScript.h"

class LuaGameActorScript : GameActorScript {
    
private:
    LuaGameActorScript(lua_State *lua);
    
public:
    static LuaGameActorScript *newInstance(std::string scriptPath);
    
public:
    virtual GameActor *loadGameActor();
    
    virtual void onError(int errorCode);
    
    virtual bool onCollide(GameActor &other);
    virtual bool onSight(GameActor &other);
    virtual bool onTargetUpdate(GameActor &other);
    
    virtual void onKeyboard();
    
private:
    lua_State *m_lua;
};

#endif /* defined(__LuaProject__LuaGameActorScript__) */
