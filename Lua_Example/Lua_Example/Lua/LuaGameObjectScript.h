//
//  LuaGameObjectScript.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/19/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__LuaGameObjectScript__
#define __LuaProject__LuaGameObjectScript__

#include <iostream>

/* Lua */
#include <lua.hpp>

#include "GameObjectScript.h"

class LuaGameObjectScript : GameObjectScript {
    
private:
    LuaGameObjectScript(lua_State *lua);
    
public:
    static LuaGameObjectScript *newInstance(std::string scriptPath);
    
public:
    virtual GameObject *loadGameObject();
    
    virtual void onError(int errorCode);
    
    virtual bool onCollide(GameObject &other);
    virtual bool onSight(GameObject &other);
    virtual bool onTargetUpdate(GameObject &other);
    
    virtual void onKeyboard();
    
private:
    lua_State *m_lua;
};

#endif /* defined(__LuaProject__LuaGameObjectScript__) */
