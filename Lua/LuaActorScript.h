//
//  LuaActorScript.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/19/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__LuaActorScript__
#define __LuaProject__LuaActorScript__

#include <iostream>

/* Lua */
#include <lua.hpp>

#include "LuaScript.h"
#include "ActorScript.h"
#include "Actor.h"

class LuaActorScript : public LuaScript<Actor>, public ActorScript {
    
public:
    LuaActorScript();
    
public:
    /* From Script API */
    virtual Actor *createNewActor(std::string filePath);
    
    virtual void onError(Actor *actor, int errorCode);
    
    virtual bool onCollide(Actor *actor, Actor *other);
    virtual bool onSight(Actor *actor, Actor *other);
    virtual bool onTargetUpdate(Actor *actor, Actor *other);
    
    virtual void onKeyboard(Actor *actor);
    
public:
    /* Internal to Lua Module */
    virtual Actor *initialize(lua_State *lua);
    
};

#endif /* defined(__LuaProject__LuaActorScript__) */
