//
//  LuaLogUtil.h
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/28/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __Turnt_Bloom__LuaLogUtil__
#define __Turnt_Bloom__LuaLogUtil__

#include <iostream>

#include <lua.hpp>

class LuaLogUtil {
    
public:
    static std::string dumpTable(lua_State *lua, int indent = 0);
};

#endif /* defined(__Turnt_Bloom__LuaLogUtil__) */
