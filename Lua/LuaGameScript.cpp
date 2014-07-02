//
//  LuaGameScript.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 6/16/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include <assert.h>
#include "LuaGameScript.h"
#include "LogManager.h"
#include "LuaLogUtil.h"

#include <lauxlib.h>
#include <lualib.h>

LuaGameScript::LuaGameScript() {}

bool
LuaGameScript::initialize(lua_State *lua, Game &game) {
    
    /* get game's _ENV */
    lua_getupvalue(lua, -1, 1);
    
#ifdef DEBUG
    assert(lua_istable(lua, -1));
    LogManager::debug(LuaLogUtil::dumpTable(lua));
#endif
    
    // TODO: read game here
    
    
    lua_pop(lua, 1);    /* remove the _ENV table */
    
#ifdef DEBUG
    /* ensure we're back to the function we were called with */
    //LogManager::debug(LuaLogUtil::dumpTable(lua));
    LogManager::debug(lua_typename(lua, lua_type(lua, -1)));
    assert(lua_isfunction(lua, -1));
#endif
    
    return true;
    
}