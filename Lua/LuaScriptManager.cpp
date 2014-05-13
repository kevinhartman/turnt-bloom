//
//  LuaScriptManager.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/26/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaScriptManager.h"
#include "LuaHelpers.h"
#include "LogManager.h"

bool
LuaScriptManager::init(std::string scriptPath) {
    
    lua_State *lua = luaL_newstate();

    if (!lua) {
        return false;
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
    
    if (!loadScript(lua, scriptPath)) {
        return false;
    }
    
    /* attach new lua state to script manager */
    m_lua = lua;
    
    LogManager::debug("Started LuaScriptManager.");
    return true;
}

bool
LuaScriptManager::loadScript(lua_State *lua, std::string scriptPath) {
    
    if (!LuaHelpers::loadFile(lua, scriptPath)) {
        LogManager::error("Failed to load game script.");
        return false;
    }
    
    if (!LuaHelpers::runFunction(lua)) {
        LogManager::error("Failed to run game script.");
        return false;
    }
    
    return true;
}

void
LuaScriptManager::shutdown() {
    lua_close(m_lua);
    LogManager::debug("Shutdown LuaScriptManager.");
}