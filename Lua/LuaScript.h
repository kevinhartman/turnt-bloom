//
//  LuaScript.h
//  Turnt Bloom
//
//  Created by Kevin Hartman on 6/30/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __Turnt_Bloom__LuaScript__
#define __Turnt_Bloom__LuaScript__

#include <lua.hpp>
#include <iostream>

#include "LuaHelpers.h"
#include "LogManager.h"

template <class T>
class LuaScript {
    
public:
    virtual bool initialize(lua_State *lua, T &object) = 0;
    
public:
    
    /*
     * Creates a new T using the function at the top of the lua stack.
     *
     * Pops the function at the top of the stack before returning.
     */
    virtual T *newInstance(lua_State *lua) {
        
        if (!lua_isfunction(lua, -1)) {
            fprintf(stderr, "** Error: A map function must be present on the top of the stack to create a new map.\n");
            return nullptr;
        }
        
        /* create a map */
        // TODO: either make this abstract, or passed in as a param
        T *map = new T();
        
        /* duplicate function so we can read the loaded environment after running */
        lua_pushvalue(lua, -1);
        
        /* load the game map into its environment.
         * Note: anything preloaded in its _ENV will be overwritten
         *       if there's a naming conflict.
         */
        if (!LuaHelpers::runFunction(lua)) {
            /* remove the map function */
            lua_pop(lua, 1);
            return nullptr;    }
        
        if (!initialize(lua, *map)) {
            /* remove the actor function */
            lua_pop(lua, 1);
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
    
    /*
     * Gets a Lua function instance of an existing map, given a GameMap.
     *
     * If the map has an associated Lua function, this function is pushed onto the stack
     * and the call returns true.
     *
     * Otherwise, nothing is pushed, and the call returns false.
     */
    virtual bool getLuaFunction(lua_State *lua, T &object) {
        
        /* get the map's environment */
        lua_pushlightuserdata(lua, (void *)&object);     /* push map address */
        lua_gettable(lua, LUA_REGISTRYINDEX);         /* get the corresponding environment */
        
        /* if there was no environment, error */
        if (lua_isnil(lua, -1)) {
            lua_pop(lua, 1);      /* remove nil */
            
            LogManager::error("No map function instance exists for supplied map.");
            return false;
        }
        
        return true;
    }
    
};


#endif /* defined(__Turnt_Bloom__LuaScript__) */
