//
//  LuaGameMapScript.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/20/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaGameMapScript.h"
#include "LuaHelpers.h"
#include "LogManager.h"
#include "LuaLogUtil.h"

#include <lauxlib.h>
#include <lualib.h>

const char* const GLOBAL_GAME_ACTORS =  "gameActors";
const char* const GLOBAL_SCRIPT =       "script";
const char* const GLOBAL_CAPTURE =      "capture";

LuaGameMapScript::LuaGameMapScript() : m_actorScript() {}

/*
 * Gets a Lua function instance of an existing map, given a GameMap.
 *
 * If the map has an associated Lua function, this function is pushed onto the stack
 * and the call returns true.
 *
 * Otherwise, nothing is pushed, and the call returns false.
 */
bool
LuaGameMapScript::getLuaGameMap(lua_State *lua, GameMap &map) {
    
    /* get the map's environment */
    lua_pushlightuserdata(lua, (void *)&map);     /* push map address */
    lua_gettable(lua, LUA_REGISTRYINDEX);         /* get the corresponding environment */
    
    /* if there was no environment, error */
    if (lua_isnil(lua, -1)) {
        lua_pop(lua, 1);      /* remove nil */
        
        LogManager::error("No map function instance exists for supplied map.");
        return false;
    }
    
    return true;
}


bool
LuaGameMapScript::initializeMap(lua_State *lua, GameMap &map) {
    
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
        
        /* verify current game object is a table */
        if (!lua_istable(lua, -1)) {
            LogManager::error("Invalid game actor.");
            
            lua_pop(lua, 1); /* remove actor */
            lua_pop(lua, 1); /* remove gameActors */
            lua_pop(lua, 1); /* remove _ENV */
            return false;
        }
        
        /* get the game object's script */
        lua_getfield(lua, -1, GLOBAL_SCRIPT);
        
        /* verify script is a function */
        if (!lua_isfunction(lua, -1)) {
            LogManager::error("Invalid game actor chunk.");
            
            lua_pop(lua, 1); /* remove invalid script/chunk */
            lua_pop(lua, 1); /* remove actor */
            lua_pop(lua, 1); /* remove gameActors */
            lua_pop(lua, 1); /* remove _ENV */
            return false;
        }
        
        /* get the game object's capture */
        lua_getfield(lua, -2, GLOBAL_CAPTURE);
        
        /* verify capture is a table */
        if (!lua_istable(lua, -1)) {
            LogManager::error("Invalid game object capture.");
            
            lua_pop(lua, 1); /* remove invalid capture */
            lua_pop(lua, 1); /* remove script/chunk */
            lua_pop(lua, 1); /* remove actor */
            lua_pop(lua, 1); /* remove gameActors */
            lua_pop(lua, 1); /* remove _ENV */
            return false;
        }
        
        /* set game object's script function's _ENV to capture */
        if(!lua_setupvalue(lua, -2, 1)) {
            LogManager::error("Map function somehow didn't have an _ENV to set...");
            
            lua_pop(lua, 1); /* remove capture */
            lua_pop(lua, 1); /* remove script/chunk */
            lua_pop(lua, 1); /* remove actor */
            lua_pop(lua, 1); /* remove gameActors */
            lua_pop(lua, 1); /* remove _ENV */
            return false;
        }
        
        /* create actor with chunk */
        GameActor *actor = /*m_actorScript.createNewGameActor(lua);*/ nullptr;
        
        /* add actor to map */
        if (actor) {
            map.addGameActor(*actor);
        } else {
            LogManager::error("Invalid actor. Skipping.");
        }
        
        objectIndex++;
        lua_pop(lua, 1); /* remove script */
        lua_pop(lua, 1); /* remove actor */
        
        lua_pushnumber(lua, objectIndex);
        lua_gettable(lua, -2);
    }
    
    lua_pop(lua, 1);    /* remove the nil */
    lua_pop(lua, 1);    /* remove the gameObjects table */
    lua_pop(lua, 1);    /* remove the _ENV table */
    
#ifdef DEBUG
    /* ensure we're back to the function we were called with */
    assert(lua_isfunction(lua, -1));
#endif
    
    return true;
    
}

/*
 * Creates a new GameMap using the function at the top of the lua stack.
 *
 * Pops the function at the top of the stack before returning.
 */
GameMap *
LuaGameMapScript::createNewGameMap(lua_State *lua) {
    
    if (!lua_isfunction(lua, -1)) {
        fprintf(stderr, "** Error: A map function must be present on the top of the stack to create a new map.\n");
        return nullptr;
    }
    
    /* create a map */
    GameMap *map = new GameMap();
    
    /* duplicate function so we can read the loaded environment after running */
    lua_pushvalue(lua, -1);
    
    /* load the game map into its environment.
     * Note: anything preloaded in its _ENV will be overwritten
     *       if there's a naming conflict.
     */
    if (!LuaHelpers::runFunction(lua)) {
        return nullptr;
    }
    
    if (!initializeMap(lua, *map)) {
        return nullptr;
    }
    
    /* store the map's instance so we can get it later */
    lua_pushlightuserdata(lua, (void *)map);    /* push map address */
    lua_pushvalue(lua, -2);                     /* push map function */
    
    /* registry[&map] = map function instance */
    lua_settable(lua, LUA_REGISTRYINDEX);

    /* remove the map function from the stack before returning */
    lua_pop(lua, 1);
     
    return map;
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

