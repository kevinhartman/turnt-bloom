//
//  GameObjectScript.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/19/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__GameObjectScript__
#define __LuaProject__GameObjectScript__

#include <iostream>

#include "GameObject.h"

class GameObjectScript {
    
public:
    virtual GameObject *loadGameObject() = 0;
    
    virtual void onError(int errorCode) = 0;
    
    virtual bool onCollide(GameObject &other) = 0;
    virtual bool onSight(GameObject &other) = 0;
    virtual bool onTargetUpdate(GameObject &other) = 0;
    
    virtual void onKeyboard() = 0;
    
};

#endif /* defined(__LuaProject__GameObjectScript__) */
