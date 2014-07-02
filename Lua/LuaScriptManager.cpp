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
#include "LuaLogUtil.h"

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
    
    /* load the map */
    if (!LuaHelpers::loadFile(lua, scriptPath)) {
        return false;
    }
    
#ifdef DEBUG
    /* print out the up value of loaded file */
    lua_getupvalue(lua, -1, 1);
    LogManager::debug(LuaLogUtil::dumpTable(lua));
    lua_pop(lua, 1);
#endif
    
    /* attach new lua state to script manager */
    m_lua = lua;
    
    LogManager::debug("Started LuaScriptManager.");
    return true;
}

bool
LuaScriptManager::createGame(Game **game) {
    
    if (!game) {
        return false;
    }
    
    /* create a new Game using the loaded file */
    *game = m_gameScript.newInstance(m_lua);
    
    if (!*game) {
        return false;
    }
    
    return true;
}

void
LuaScriptManager::shutdown() {
    lua_close(m_lua);
    LogManager::debug("Shutdown LuaScriptManager.");
}