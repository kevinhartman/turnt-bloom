//
//  LuaGameObjectScript.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/19/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaGameObjectScript.h"

#include <lauxlib.h>
#include <lualib.h>

LuaGameObjectScript::LuaGameObjectScript(lua_State *lua) : m_lua(lua) {}

LuaGameObjectScript *
LuaGameObjectScript::newInstance(std::string scriptPath) {
    
    lua_State *lua = luaL_newstate();
    
    if (!lua) {
        return nullptr;
    }
    
    /* Lua libraries for GameObject scripts */
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
            fprintf(stderr, "** Error loading %s: Game object not found.\n", scriptPath.c_str());
            return nullptr;
            
        case LUA_ERRSYNTAX:
            fprintf(stderr, "** Error loading %s: Syntax error.\n", scriptPath.c_str());
            return nullptr;
            
        case LUA_ERRMEM:
            fprintf(stderr, "** Error loading %s: Memory allocation error.\n", scriptPath.c_str());
            return nullptr;
            
        default:
            fprintf(stdout, "Loaded game object %s", scriptPath.c_str());
    }

    
    return new LuaGameObjectScript(lua);
}

GameObject *
LuaGameObjectScript::loadGameObject() {
    // TODO: stubbed
    return nullptr;
}

void
LuaGameObjectScript::onError(int errorCode) {
    // TODO: stubbed
    return;
}

bool
LuaGameObjectScript::onCollide(GameObject &other) {
    // TODO: stubbed
    return false;
}

bool
LuaGameObjectScript::onSight(GameObject &other) {
    // TODO: stubbed
    return false;
}

bool
LuaGameObjectScript::onTargetUpdate(GameObject &other) {
    // TODO: stubbed
    return false;
}

void
LuaGameObjectScript::onKeyboard() {
    // TODO: stubbed
    return;
}