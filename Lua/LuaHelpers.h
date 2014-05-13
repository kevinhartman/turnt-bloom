//
//  LuaHelpers.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/22/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__LuaHelpers__
#define __LuaProject__LuaHelpers__

#include <iostream>

#include <lua.hpp>

class LuaHelpers {
    
public:
    static bool getVec3(lua_State *lua, lua_Number *vec3);
    static bool getVec4(lua_State *lua, lua_Number *vec4);
    static bool getfield (lua_State *lua, const char *key, lua_Number *value);
    
    static bool loadLibs(lua_State *lua);
    static bool loadFile(lua_State *lua, std::string scriptPath);
    static bool runFunction(lua_State *lua);
};

#endif /* defined(__LuaProject__LuaHelpers__) */
