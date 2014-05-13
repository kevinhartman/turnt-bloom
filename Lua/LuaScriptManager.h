//
//  LuaScriptManager.h
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/26/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __Turnt_Bloom__LuaScriptManager__
#define __Turnt_Bloom__LuaScriptManager__

#include <iostream>

#include "ScriptManager.h"

#include <lua.hpp>

class LuaScriptManager : ScriptManager {
    
private:
    LuaScriptManager() {};
    LuaScriptManager(LuaScriptManager const&);
    void operator=(LuaScriptManager const&);
    
public:
    static ScriptManager *getInstance()
    {
        static LuaScriptManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return &instance;
    }
    
public:
    virtual bool init(std::string scriptPath);
    virtual void shutdown();
    
private:
    static bool loadScript(lua_State *lua, std::string scriptPath);
    
private:
    lua_State *m_lua;
    
};

#endif /* defined(__Turnt_Bloom__LuaScriptManager__) */
