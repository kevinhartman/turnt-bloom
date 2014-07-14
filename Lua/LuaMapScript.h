//
//  LuaMapScript.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/20/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__LuaMapScript__
#define __LuaProject__LuaMapScript__

#include <iostream>
#include <map>

/* Lua */
#include <lua.hpp>

#include "LuaScript.h"
#include "MapScript.h"
#include "Map.h"
#include "LuaActorScript.h"

class LuaMapScript : public LuaScript<Map>, public MapScript {
    
public:
    LuaMapScript();
    
public:
    /* From Script API */
    virtual Map *createNewMap(std::string filePath);
    
public:
    /* Internal to Lua module */
    virtual Map *initialize(lua_State *lua);

    // TODO: what is this method for?
public:
    void updateScene(lua_State *lua, Map &map, double timeElapsed);
    
private:
    LuaActorScript m_actorScript;
    
};

#endif /* defined(__LuaProject__LuaMapScript__) */
