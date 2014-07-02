//
//  LuaGameScript.h
//  Turnt Bloom
//
//  Created by Kevin Hartman on 6/16/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __Turnt_Bloom__LuaGameScript__
#define __Turnt_Bloom__LuaGameScript__

#include <iostream>

/* Lua */
#include <lua.hpp>

#include "Game.h"
#include "LuaScript.h"

class LuaGameScript : public LuaScript<Game> {
    
public:
    LuaGameScript();
    
    virtual bool initialize(lua_State *lua, Game &game);
    
};

#endif /* defined(__Turnt_Bloom__LuaGameScript__) */
