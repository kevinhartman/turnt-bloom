//
//  GameMapScript.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/20/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__GameMapScript__
#define __LuaProject__GameMapScript__

#include <iostream>

#include "GameMap.h"

class GameMapScript {
    
public:
    virtual GameMap *loadGameMap() = 0;
};

#endif /* defined(__LuaProject__GameMapScript__) */
