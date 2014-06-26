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

class LuaGameScript {
    
public:
    LuaGameScript();
    
public:
    Game *createNewGame(lua_State *lua);
    
private:
    bool getLuaGame(lua_State *lua, Game &game);
    bool initializeGame(lua_State *lua, Game &game);
    
};

#endif /* defined(__Turnt_Bloom__LuaGameScript__) */
