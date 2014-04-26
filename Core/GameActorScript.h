//
//  GameActorScript.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/19/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__GameActorScript__
#define __LuaProject__GameActorScript__

#include <iostream>

#include "GameActor.h"

class GameActorScript {
    
public:
    virtual GameActor *loadGameActor() = 0;
    
    virtual void onError(int errorCode) = 0;
    
    virtual bool onCollide(GameActor &other) = 0;
    virtual bool onSight(GameActor &other) = 0;
    virtual bool onTargetUpdate(GameActor &other) = 0;
    
    virtual void onKeyboard() = 0;
    
};

#endif /* defined(__LuaProject__GameActorScript__) */
