//
//  LuaGameMapScript.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/20/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaGameMapScript.h"
#include "LuaScriptHelpers.h"
#include "LogManager.h"
#include "LuaLogUtil.h"

#include <lauxlib.h>
#include <lualib.h>

const char* const GLOBAL_GAME_ACTORS =  "gameActors";
const char* const GLOBAL_SCRIPT =       "script";
const char* const GLOBAL_CAPTURE =      "capture";

LuaGameMapScript::LuaGameMapScript() : m_actorScript() {}

bool
LuaGameMapScript::initialize(lua_State *lua, GameMap &map) {
    
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
        LogManager::error("No gameActors table in map.");
        
        lua_pop(lua, 1); /* remove invalid gameActors */
        lua_pop(lua, 1); /* remove _ENV */
        return false;
    }
    
    int objectIndex = 1;
    lua_pushnumber(lua, objectIndex);
    lua_gettable(lua, -2);
    
    while (!lua_isnil(lua, -1)) {
        
        if (!LuaScriptHelpers::initFunctionWithBlock(lua)) {
            lua_pop(lua, 1); /* remove block */
            lua_pop(lua, 1); /* remove gameActors */
            lua_pop(lua, 1); /* remove _ENV */
            return false;
        }
        
        /* create actor with chunk */
        GameActor *actor = m_actorScript.newInstance(lua);
        
        /* add actor to map */
        if (actor) {
            map.addGameActor(*actor);
        } else {
            LogManager::error("Invalid actor. Skipping.");
        }
        
        objectIndex++;
        lua_pop(lua, 1); /* remove block */
        
        lua_pushnumber(lua, objectIndex);
        lua_gettable(lua, -2);
    }
    
    lua_pop(lua, 1);    /* remove the nil */
    lua_pop(lua, 1);    /* remove the gameActor blocks table */
    lua_pop(lua, 1);    /* remove the _ENV table */
    
#ifdef DEBUG
    /* ensure we're back to the function we were called with */
    //LogManager::debug(LuaLogUtil::dumpTable(lua));
    LogManager::debug(lua_typename(lua, lua_type(lua, -1)));
    assert(lua_isfunction(lua, -1));
#endif
    
    return true;
    
}

void
LuaGameMapScript::updateScene(lua_State *lua, GameMap &map, double timeElapsed) {
    // TODO: this could be done better. maybe (N/D)^2, where D is cell divisions of map
    
    std::map<GameActor *, std::vector<GameActor *> *> collisions;
    std::map<GameActor *, std::vector<GameActor *> *> sightings;
    
    map.computeInteractions(collisions, sightings);
    
    std::map<GameActor *, std::vector<GameActor *> *>::iterator iter;
    
    /* call game object script with collision data */
    for (iter = collisions.begin(); iter != collisions.end(); ++iter) {
        
        GameActor *object = iter->first;
        
        // TODO: call script collision callback with iter->second
        // use script in m_map w.e
        
    }
    
    /* call game object script with sighting data */
    for (iter = sightings.begin(); iter != sightings.end(); ++iter) {
        
        GameActor *object = iter->first;
        
        // TODO: call script sightings callback with iter->second
        
    }
    
}

