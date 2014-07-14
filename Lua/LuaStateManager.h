//
//  LuaStateManager.h
//  Turnt Bloom
//
//  Created by Kevin Hartman on 7/10/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __Turnt_Bloom__LuaStateManager__
#define __Turnt_Bloom__LuaStateManager__

#include <iostream>

#include <lua.hpp>

class LuaStateManager {
    
public:
    static lua_State *getLuaState();
};

#endif /* defined(__Turnt_Bloom__LuaStateManager__) */
