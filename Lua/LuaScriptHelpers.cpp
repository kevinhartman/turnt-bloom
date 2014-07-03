//
//  LuaScriptHelpers.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 7/3/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaScriptHelpers.h"
#include "LogManager.h"

const char* const GLOBAL_SCRIPT =       "script";
const char* const GLOBAL_CAPTURE =      "capture";

/**
 * Expects an object init block at the top of the stack.
 * On success, pushes a function generated from the provided block to the stack
 * and returns true. Otherwise, the stack is unmodified and false is returned.
 */
bool
LuaScriptHelpers::initFunctionWithBlock(lua_State *lua) {
    /* verify block is a table */
    if (!lua_istable(lua, -1)) {
        LogManager::error("Invalid game actor.");
        
        return false;
    }
    
    /* get the block's script value */
    lua_getfield(lua, -1, GLOBAL_SCRIPT);
    
    /* verify script is a function */
    if (!lua_isfunction(lua, -1)) {
        LogManager::error("Invalid game actor chunk.");
        
        lua_pop(lua, 1); /* remove invalid script/chunk */
        
        return false;
    }
    
    /* get the block's capture */
    lua_getfield(lua, -2, GLOBAL_CAPTURE);
    
    /* verify capture is a table */
    if (!lua_istable(lua, -1)) {
        LogManager::error("Invalid game object capture.");
        
        lua_pop(lua, 1); /* remove invalid capture */
        lua_pop(lua, 1); /* remove script/chunk */
        
        return false;
    }
    
    /* set block's script _ENV to capture */
    if(!lua_setupvalue(lua, -2, 1)) {
        LogManager::error("Map function somehow didn't have an _ENV to set...");
        
        // TODO: does setupvalue modify the stack when it fails?
        lua_pop(lua, 1); /* remove capture */
        lua_pop(lua, 1); /* remove script/chunk */
        
        return false;
    }
    
    return true;
}