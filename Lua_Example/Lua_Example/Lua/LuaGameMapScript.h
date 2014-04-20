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

/* Lua */
#include <lua.hpp>

#include "GameMapScript.h"

class LuaGameMapScript : GameMapScript {
    
private:
    LuaGameMapScript(lua_State *lua);
    
public:
    static LuaGameMapScript *newInstance(std::string scriptPath);
    
public:
    virtual GameMap *loadGameMap();
    
private:
    lua_State *m_lua;
    
};

#endif /* defined(__LuaProject__LuaGameMapScript__) */
