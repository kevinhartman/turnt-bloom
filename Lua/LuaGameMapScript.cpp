//
//  LuaGameMapScript.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/20/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaGameMapScript.h"
#include "LuaHelpers.h"

#include <lauxlib.h>
#include <lualib.h>

const char* const GLOBAL_GAME_OBJECTS = "gameObjects";
const char* const GLOBAL_SCRIPT =       "script";

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
            //TODO: check for unspecified errors
        default:
            printf("Loaded map %s\n", scriptPath.c_str());
    }
    
    result = lua_pcall(m_lua, 0, LUA_MULTRET, 0);
    
    switch (result) {
        case LUA_ERRRUN:
            fprintf(stderr, "** Error running %s: Runtime error.\n", scriptPath.c_str());
            return false;
            
        case LUA_ERRMEM:
            fprintf(stderr, "** Error running %s: Memory error.\n", scriptPath.c_str());
            return false;
            
        case LUA_ERRERR:
            fprintf(stderr, "** Error running %s: Error handler error.\n", scriptPath.c_str());
            return false;
            //TODO: check for unspecified errors
        default:
            printf("Ran map %s\n", scriptPath.c_str());
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
    
    /* Get motion attributes */
    lua_getglobal(m_lua, GLOBAL_GAME_OBJECTS);
    //TODO: check nil for gameobjects
    
    int objectIndex = 1;
    lua_pushnumber(m_lua, objectIndex);
    lua_gettable(m_lua, -2);
    
    while (!lua_isnil(m_lua, -1)) {
        
        if (!lua_istable(m_lua, -1)) {
            fprintf(stderr, "Invalid game object in map.\n");
            
            lua_pop(m_lua, 1); /* remove invalid object */
            lua_pop(m_lua, 1); /* remove gameObjects table */
            return false;
        }
        
        lua_getfield(m_lua, -1, GLOBAL_SCRIPT);
        
        if (!lua_isfunction(m_lua, -1)) {
            fprintf(stderr, "Invalid script specified in game object initializer.\n");
            
            lua_pop(m_lua, 1); /* remove invalid object */
            lua_pop(m_lua, 1); /* remove gameObjects table */
            return false;
        }
        
        lua_setupvalue(m_lua, -1, -2);
        
        // TODO create and add GameObjects here
        
        objectIndex++;
        lua_pop(m_lua, 1); /* remove script */
        lua_pushnumber(m_lua, objectIndex);
        lua_gettable(m_lua, -2);
    }
    
    lua_pop(m_lua, 1);  /* remove the nil */
    lua_pop(m_lua, 1);  /* remove the gameObjects table */
    
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
    
    initializeMap(*map);
    
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

