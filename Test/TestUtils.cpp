//
//  TestUtils.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/28/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "TestUtils.h"

bool
TestUtils::createLuaState(lua_State **lua) {
    
    /* param guard */
    if (!lua) {
        return false;
    }
    
    *lua = luaL_newstate();
    
    /* new state creation check */
    if (!lua) {
        return false;
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
        lib->func(*lua);
        lua_settop(*lua, 0);
    }
    
    return true;
}