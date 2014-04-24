//
//  ScriptEngine.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/17/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__ScriptEngine__
#define __LuaProject__ScriptEngine__

#include <iostream>
#include <lua.hpp>

#include "GameMap.h"

class ScriptEngine {
public:
    ScriptEngine();
    
public:
    void updateScene(GameMap &map, double timeElapsed);
    
private:
    lua_State *m_lua;
};


#endif /* defined(__LuaProject__ScriptEngine__) */