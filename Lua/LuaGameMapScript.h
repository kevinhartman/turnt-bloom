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

#include "GameMapScript.h"

class LuaGameMapScript : GameMapScript {
    
private:
    LuaGameMapScript(lua_State *lua);
    
public:
    static LuaGameMapScript *newInstance();
    
public:
    virtual GameMap *createNewGameMap(lua_State *lua);
    virtual void updateScene(GameMap &map, double timeElapsed);
    
private:
    bool loadScript(std::string scriptPath);
    void setEnvironmentFor(GameMap &map);
    bool initializeMap(GameMap &map);
    
private:
    lua_State *m_lua;
    
    
};

#endif /* defined(__LuaProject__LuaGameMapScript__) */
