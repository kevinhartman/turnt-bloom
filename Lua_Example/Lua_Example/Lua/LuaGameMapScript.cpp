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

const char* const GLOBAL_POSITION =         "position";
const char* const GLOBAL_DIRECTION =        "direction";
const char* const GLOBAL_SPEED =            "speed";
const char* const GLOBAL_EYELINE =          "eyeline";
const char* const GLOBAL_FIELD_OF_VIEW =    "fieldOfView";
const char* const GLOBAL_VISION_DEPTH =     "visionDepth";
const char* const GLOBAL_BODY_RADIUS =      "bodyRadius";


LuaGameMapScript::LuaGameMapScript(lua_State *lua) : m_lua(lua) {}

LuaGameMapScript *
LuaGameMapScript::newInstance() {
    
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
    
    return new LuaGameMapScript(lua);
}

bool
LuaGameMapScript::loadScript(std::string scriptPath) {
    // TODO: stubbed
    
    int result = luaL_loadfile(m_lua, scriptPath.c_str());
    
    switch (result) {
        case LUA_ERRFILE:
            fprintf(stderr, "** Error loading %s: Map not found.\n", scriptPath.c_str());
            return false;
            
        case LUA_ERRSYNTAX:
            fprintf(stderr, "** Error loading %s: Syntax error.\n", scriptPath.c_str());
            return false;
            
        case LUA_ERRMEM:
            fprintf(stderr, "** Error loading %s: Memory allocation error.\n", scriptPath.c_str());
            return false;
            
        default:
            printf("Loaded map %s", scriptPath.c_str());
    }
    
    return true;
}

// TODO: explode on error
void
LuaGameMapScript::setEnvironmentFor(GameMap &map) {
    
    /* get the map's environment */
    lua_pushlightuserdata(m_lua, (void *)&map);     /* push map address */
    lua_gettable(m_lua, LUA_REGISTRYINDEX);         /* get the corresponding environment */
    
    /* if there was no environment, error */
    if (lua_isnil(m_lua, -1)) {
        lua_pop(m_lua, 1);      /* remove nil */
        
        fprintf(stderr, "No environment exists for supplied map.\n");
        return;
    }
    
    /* set the current environment to map's environment */
    lua_setglobal(m_lua, "_ENV");
}

bool
LuaGameMapScript::initializeMap(GameMap &map) {
    // STUBBED
    return false;
    
}

GameMap *
LuaGameMapScript::createNewGameMap(std::string scriptPath) {
    
    /* create an empty table */
    lua_newtable(m_lua);
    
    /* set the current environment to empty */
    lua_setglobal(m_lua, "_ENV");
    
    /* attempt to load script into environment */
    if (!loadScript(scriptPath)) {
        return nullptr;
    }
    
    /* create a map */
    GameMap *map = new GameMap();
    
    /* store the current environment */
    lua_pushlightuserdata(m_lua, (void *)map);  /* push map address */
    lua_getglobal(m_lua, "_ENV");               /* push environment */
    
#ifdef DEBUG
    assert(!lua_isnil(m_lua, -1));
#endif
    
    /* registry[map] = _ENV */
    lua_settable(m_lua, LUA_REGISTRYINDEX);
    
    
    /* This is where you create GameObjects that will be in this GameMap.
     * Use their script to make them and add the resulting GameObjects
     * to this map.
     
     Note: might want to make this a friend class to GameMap
     */
    
    /*
     
     Create a new GameMap.
     
     For each game object in the script game map,
        create (createGameObject) an object using game object script
        map (mem var) gameobject to luascriptobject
        initialize the object using game map info
     
        add GameObject to GameMap
     
     */
     
    return nullptr;
}

void
LuaGameMapScript::updateScene(GameMap &map, double timeElapsed) {
    // TODO: this could be done better. maybe (N/D)^2, where D is cell divisions of map
    
    std::map<GameObject *, std::vector<GameObject *> *> collisions;
    std::map<GameObject *, std::vector<GameObject *> *> sightings;
    
    map.computeInteractions(collisions, sightings);
    
    std::map<GameObject *, std::vector<GameObject *> *>::iterator iter;
    
    /* call game object script with collision data */
    for (iter = collisions.begin(); iter != collisions.end(); ++iter) {
        
        GameObject *object = iter->first;
        
        // TODO: call script collision callback with iter->second
        // use script in m_map w.e
        
    }
    
    /* call game object script with sighting data */
    for (iter = sightings.begin(); iter != sightings.end(); ++iter) {
        
        GameObject *object = iter->first;
        
        // TODO: call script sightings callback with iter->second
        
    }
    
}

