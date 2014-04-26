//
//  LuaGameActorScript.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/19/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaGameActorScript.h"

#include <lauxlib.h>
#include <lualib.h>

const char* const GLOBAL_POSITION =         "position";
const char* const GLOBAL_DIRECTION =        "direction";
const char* const GLOBAL_SPEED =            "speed";
const char* const GLOBAL_EYELINE =          "eyeline";
const char* const GLOBAL_FIELD_OF_VIEW =    "fieldOfView";
const char* const GLOBAL_VISION_DEPTH =     "visionDepth";
const char* const GLOBAL_BODY_RADIUS =      "bodyRadius";


LuaGameActorScript::LuaGameActorScript(lua_State *lua) : m_lua(lua) {}

LuaGameActorScript *
LuaGameActorScript::newInstance(std::string scriptPath) {
    
    lua_State *lua = luaL_newstate();
    
    if (!lua) {
        return nullptr;
    }
    
    /* Lua libraries for GameActor scripts */
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

    
    return new LuaGameActorScript(lua);
}

GameActor *
LuaGameActorScript::loadGameActor() {
    // TODO: stubbed
    
    
    /* Get motion attributes */
//    lua_getglobal(m_lua, GLOBAL_POSITION);
//    
//    lua_Number position[3];
//    if (!LuaHelpers::getVec3(m_lua, position)) {
//        fprintf(stderr, "%s is invalid.\n", GLOBAL_POSITION);
//        return false;
//    }
//    
//    lua_pop(m_lua, 1);
//    
//    lua_getglobal(m_lua, GLOBAL_DIRECTION);
//    
//    lua_Number direction[3];
//    if (!LuaHelpers::getVec3(m_lua, direction)) {
//        fprintf(stderr, "%s is invalid.\n", GLOBAL_DIRECTION);
//        return false;
//    }
//    
//    lua_getglobal(m_lua, GLOBAL_SPEED);
//    lua_Number speed = lua_tonumber(m_lua, -1);
//    printf("[C++] speed = %f\n", speed);
//    
//    
//    lua_getglobal(m_lua, GLOBAL_FIELD_OF_VIEW);
//    lua_Number fieldOfView = lua_tonumber(m_lua, -1);
//    printf("[C++] fieldOfView = %f\n", fieldOfView);
//    
//    lua_getglobal(m_lua, GLOBAL_VISION_DEPTH);
//    lua_Number visionDepth = lua_tonumber(m_lua, -1);
//    printf("[C++] visionDepth = %f\n", visionDepth);
//    
//    lua_getglobal(m_lua, GLOBAL_BODY_RADIUS);
//    lua_Number bodyRadius = lua_tonumber(m_lua, -1);
//    printf("[C++] bodyRadius = %f\n", bodyRadius);
    return nullptr;
}

void
LuaGameActorScript::onError(int errorCode) {
    // TODO: stubbed
    return;
}

bool
LuaGameActorScript::onCollide(GameActor &other) {
    // TODO: stubbed
    return false;
}

bool
LuaGameActorScript::onSight(GameActor &other) {
    // TODO: stubbed
    return false;
}

bool
LuaGameActorScript::onTargetUpdate(GameActor &other) {
    // TODO: stubbed
    return false;
}

void
LuaGameActorScript::onKeyboard() {
    // TODO: stubbed
    return;
}