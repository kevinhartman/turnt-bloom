//
//  LuaGameMapScript.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/20/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaGameMapScript.h"

#include <lauxlib.h>
#include <lualib.h>

LuaGameMapScript::LuaGameMapScript(lua_State *lua) : m_lua(lua) {}

LuaGameMapScript *
LuaGameMapScript::newInstance(std::string scriptPath) {
    
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
    
    int result = luaL_loadfile(lua, scriptPath.c_str());
    
    switch (result) {
        case LUA_ERRFILE:
            fprintf(stderr, "** Error loading %s: Map not found.\n", scriptPath.c_str());
            return nullptr;
            
        case LUA_ERRSYNTAX:
            fprintf(stderr, "** Error loading %s: Syntax error.\n", scriptPath.c_str());
            return nullptr;
            
        case LUA_ERRMEM:
            fprintf(stderr, "** Error loading %s: Memory allocation error.\n", scriptPath.c_str());
            return nullptr;
            
        default:
            fprintf(stdout, "Loaded map %s", scriptPath.c_str());
    }
    
    return new LuaGameMapScript(lua);
}

GameMap *
LuaGameMapScript::loadGameMap() {
    return nullptr;
}

