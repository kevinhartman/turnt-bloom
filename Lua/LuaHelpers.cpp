//
//  LuaHelpers.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/22/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaHelpers.h"

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