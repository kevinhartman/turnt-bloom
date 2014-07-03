//
//  LuaScriptHelpers.h
//  Turnt Bloom
//
//  Created by Kevin Hartman on 7/3/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __Turnt_Bloom__LuaScriptHelpers__
#define __Turnt_Bloom__LuaScriptHelpers__

#include <iostream>
#include <lua.hpp>

class LuaScriptHelpers {
public:
    static bool initFunctionWithBlock(lua_State *lua);
};

#endif /* defined(__Turnt_Bloom__LuaScriptHelpers__) */
