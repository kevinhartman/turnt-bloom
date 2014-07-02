//
//  LuaGameMapScript.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/20/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__LuaGameMapScript__
#define __LuaProject__LuaGameMapScript__

#include <iostream>
#include <map>

/* Lua */
#include <lua.hpp>

#include "LuaScript.h"
#include "GameMap.h"
#include "LuaGameActorScript.h"

class LuaGameMapScript : public LuaScript<GameMap> {
    
public:
    LuaGameMapScript();
    
    virtual bool initialize(lua_State *lua, GameMap &map);

public:
    void updateScene(lua_State *lua, GameMap &map, double timeElapsed);
    
private:
    LuaGameActorScript m_actorScript;
    
};

#endif /* defined(__LuaProject__LuaGameMapScript__) */
