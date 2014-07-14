//
//  LuaMapScript.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/20/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaMapScript.h"
#include "LuaScriptHelpers.h"
#include "LogManager.h"
#include "LuaLogUtil.h"
#include "LuaStateManager.h"

#include <lauxlib.h>
#include <lualib.h>

const char* const GLOBAL_GAME_ACTORS =  "actors";
const char* const GLOBAL_SCRIPT =       "script";
const char* const GLOBAL_CAPTURE =      "capture";

LuaMapScript::LuaMapScript() : m_actorScript() {}

Map *
LuaMapScript::createNewMap(std::string filePath) {
    
    lua_State *lua = LuaStateManager::getLuaState();
    
    // TODO: set stack to empty?
    
    /* load the game from script */
    if (!LuaHelpers::loadFile(lua, filePath)) {
        // TODO: is cleanup required on fail?
        return nullptr;
    }
    
#ifdef DEBUG
    /* print out the up value of loaded file */
    lua_getupvalue(lua, -1, 1);
    LogManager::debug(LuaLogUtil::dumpTable(lua));
    lua_pop(lua, 1);
#endif
    
    return newInstance(lua);
}

Map *
LuaMapScript::initialize(lua_State *lua) {
    
    Map *map = new Map();
    
    /* get map's _ENV */
    lua_getupvalue(lua, -1, 1);
    
#ifdef DEBUG
    assert(lua_istable(lua, -1));
    LogManager::debug(LuaLogUtil::dumpTable(lua));
#endif
    
    /* get game actors */
    lua_getfield(lua, -1, GLOBAL_GAME_ACTORS);
    
    /* ensure there's a table of game actors */
    if (!lua_istable(lua, -1)) {
        LogManager::error("No actors table in map.");
        
        lua_pop(lua, 1); /* remove invalid actors */
        lua_pop(lua, 1); /* remove _ENV */
        return nullptr;
    }
    
    int objectIndex = 1;
    lua_pushnumber(lua, objectIndex);
    lua_gettable(lua, -2);
    
    while (!lua_isnil(lua, -1)) {
        
        if (!LuaScriptHelpers::initFunctionWithBlock(lua)) {
            lua_pop(lua, 1); /* remove block */
            lua_pop(lua, 1); /* remove actors */
            lua_pop(lua, 1); /* remove _ENV */
            return nullptr;
        }
        
        /* create actor with chunk */
        Actor *actor = m_actorScript.newInstance(lua);
        
        /* add actor to map */
        if (actor) {
            map->addActor(*actor);
        } else {
            LogManager::error("Invalid actor. Skipping.");
        }
        
        objectIndex++;
        lua_pop(lua, 1); /* remove block */
        
        lua_pushnumber(lua, objectIndex);
        lua_gettable(lua, -2);
    }
    
    lua_pop(lua, 1);    /* remove the nil */
    lua_pop(lua, 1);    /* remove the actor blocks table */
    lua_pop(lua, 1);    /* remove the _ENV table */
    
#ifdef DEBUG
    /* ensure we're back to the function we were called with */
    //LogManager::debug(LuaLogUtil::dumpTable(lua));
    LogManager::debug(lua_typename(lua, lua_type(lua, -1)));
    assert(lua_isfunction(lua, -1));
#endif
    
    return map;
    
}