//
//  LuaScriptManager.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/26/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaScriptManager.h"

#include <lua.hpp>

bool
LuaScriptManager::init(/* game script */) {
    
    lua_State *lua = luaL_newstate();
    
    if (!lua) {
        return nullptr;
    }
    
    /* Lua libraries for GameMap scripts */
    static const luaL_Reg lualibs[] =
    {
        { "base", luaopen_base },
        { "io", luaopen_io },
        { NULL, NULL}
    };
    
    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        lib->func(lua);
        lua_settop(lua, 0);
    }
    
    
    printf("Started LuaScriptManager.\n");
    return true;
}

void
LuaScriptManager::shutdown() {
    printf("Shutdown LuaScriptManager.\n");
}