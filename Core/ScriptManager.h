//
//  ScriptManager.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/17/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__ScriptManager__
#define __LuaProject__ScriptManager__

#include "Game.h"

#include <iostream>


class ScriptManager {
    
public:
    virtual bool init(std::string scriptPath) = 0;
    virtual void shutdown() = 0;
    
//public:
//    void updateScene(GameMap &map, double timeElapsed);
    
    virtual bool createGame(Game **game) = 0;
    
    
};


#endif /* defined(__LuaProject__ScriptManager__) */
