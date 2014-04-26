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
    virtual bool init(/* game script */);
    virtual void shutdown();
    
};

#endif /* defined(__Turnt_Bloom__LuaScriptManager__) */
