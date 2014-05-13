//
//  LuaHelpers.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/22/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaHelpers.h"
#include "LogManager.h"
#include "LuaLogUtil.h"
#include <assert.h>

const char* const XYZW_KEYS[] = {
    "x",
    "y",
    "z",
    "w",
};

/* assume that table is on the stack top */
bool
LuaHelpers::getVec3(lua_State *lua, lua_Number *vec3) {
    
    if (!lua_istable(lua, -1)) {
        return false;
    }
    
    for (int i = 0; i < 3; i++) {
        if (!getfield(lua, XYZW_KEYS[i], &vec3[i])) {
            return false;
        }
    }
    
    return true;
}

/* assume that table is on the stack top */
bool
LuaHelpers::getVec4(lua_State *lua, lua_Number *vec4) {
    
    if (!lua_istable(lua, -1)) {
        return false;
    }
    
    for (int i = 0; i < 4; i++) {
        if (!getfield(lua, XYZW_KEYS[i], &vec4[i])) {
            return false;
        }
    }
    
    return true;
}

/* assume that table is on the stack top */
bool
LuaHelpers::getfield(lua_State *lua, const char *key, lua_Number *value) {
    
    lua_Number result;
    lua_pushstring(lua, key);
    lua_gettable(lua, -2);  /* get table[key] */
    
    if (!lua_isnumber(lua, -1)) {
        fprintf(stderr, "Invalid component in table.\n");
        return false;
    }
    
    result = lua_tonumber(lua, -1);
    lua_pop(lua, 1);  /* remove number */
    
    *value = result;
    
    return true;
}

bool
LuaHelpers::loadFile(lua_State *lua, std::string scriptPath) {
    
    int result = luaL_loadfile(lua, scriptPath.c_str());
    
    switch (result) {
        case LUA_ERRFILE:
            fprintf(stderr, "** Error loading %s: Script not found.\n", scriptPath.c_str());
            return false;
            
        case LUA_ERRSYNTAX:
            fprintf(stderr, "** Error loading %s: Syntax error.\n", scriptPath.c_str());
            return false;
            
        case LUA_ERRMEM:
            fprintf(stderr, "** Error loading %s: Memory allocation error.\n", scriptPath.c_str());
            return false;
            //TODO: check for unspecified errors
        default:
            printf("Loaded %s\n", scriptPath.c_str());
    }
    
    return true;
}

bool
LuaHelpers::runFunction(lua_State *lua) {
    
    // TODO: remove any errors on stack after this function is run
    
    int result = lua_pcall(lua, 0, LUA_MULTRET, 0);
    
    switch (result) {
        case LUA_ERRRUN:
            fprintf(stderr, "** Error running function: Runtime error.\n");
            return false;
            
        case LUA_ERRMEM:
            fprintf(stderr, "** Error running function: Memory error.\n");
            return false;
            
        case LUA_ERRERR:
            fprintf(stderr, "** Error running function: Error handler error.\n");
            return false;
            //TODO: check for unspecified errors
        default:
            printf("Ran function.\n");
    }
    
    return true;
}

// TODO: libs are only in return _ENV table, not inside its _G
/*
 * Pushes a table onto the stack that contains default lua libraries.
 */
bool
LuaHelpers::loadLibs(lua_State *lua) {
    
    /* Lua libraries */
    static const luaL_Reg lualibs[] = {
        {"_G", luaopen_base},
        {LUA_LOADLIBNAME, luaopen_package},
        {LUA_COLIBNAME, luaopen_coroutine},
        {LUA_TABLIBNAME, luaopen_table},
        {LUA_IOLIBNAME, luaopen_io},
        /*{LUA_OSLIBNAME, luaopen_os},*/ /* no OS probably */
        {LUA_STRLIBNAME, luaopen_string},
        {LUA_BITLIBNAME, luaopen_bit32},
        /*{LUA_MATHLIBNAME, luaopen_math},*/
        {LUA_DBLIBNAME, luaopen_debug},
        {NULL, NULL}
    };
    
    luaL_newlib(lua, lualibs);
    
    int libIndex = 0;
    
    /* load libraries into new environment */
    while (lualibs[libIndex].func) {
        
        /* push the library name */
        lua_pushstring(lua, lualibs[libIndex].name);
        
        /* get the library function */
        lua_gettable(lua, -2);
        
        /* call the function to get it's table */
        if(!LuaHelpers::runFunction(lua)) {
            // TODO: add library name when logging tool is improved
            LogManager::error("Unable to load library.");
            
            assert(false); // TODO: because runFunction leaves an error, stack will be unbalanced here and we need to stop
            
            libIndex++;
            continue;
        }
        
        /* replace library function with table containing its function */
        lua_setfield(lua, -2, lualibs[libIndex].name);
        
        libIndex++;
    }
    
    /* add Lua base lib stuff to _ENV metatable */
    
    /* create new metatable */
    lua_newtable(lua);
    
    /* get global table */
    lua_pushstring(lua, "_G");
    lua_gettable(lua, -3);
    
    /* set __index for new metatable to _G */
    lua_setfield(lua, -2, "__index");
    
    /* set new _ENV metatable to this metatable */
    lua_setmetatable(lua, -2);
    
    return true;
}