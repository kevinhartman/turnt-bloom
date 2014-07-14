//
//  LuaStateManager.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 7/10/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaStateManager.h"

lua_State *
LuaStateManager::getLuaState() {
    
    // will this be called for each call to getLuaState? we don't want that
    static lua_State *lua = luaL_newstate();
    
    if (!lua) {
        return nullptr;
    }
    
    /* Lua libraries */
    static const luaL_Reg lualibs[] = {
        {"_G", luaopen_base},
        {LUA_LOADLIBNAME, luaopen_package},
        {LUA_COLIBNAME, luaopen_coroutine},
        {LUA_TABLIBNAME, luaopen_table},
        {LUA_IOLIBNAME, luaopen_io},
        /*{LUA_OSLIBNAME, luaopen_os},*/ /* no OS probably */
        {LUA_STRLIBNAME, luaopen_string},
        {LUA_BITLIBNAME, luaopen_bit32},
        {LUA_MATHLIBNAME, luaopen_math},
        {LUA_DBLIBNAME, luaopen_debug},
        {NULL, NULL}
    };
    
    /* globally load default libraries */
    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++) {
        lib->func(lua);
        lua_settop(lua, 0);
    }
    
    return lua;
}