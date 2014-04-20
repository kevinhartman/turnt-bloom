//
//  GameMap.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/18/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__GameMap__
#define __LuaProject__GameMap__

#include <iostream>
#include <vector>
#include <map>

#include "GameObject.h"

#endif /* defined(__LuaProject__GameMap__) */

class GameMap {
public:
    GameMap();
    
public:
    void updateScene(double timeElapsed);
    void computeInteractions(std::map<GameObject *, std::vector<GameObject *> *> &collisions,
                             std::map<GameObject *, std::vector<GameObject *> *> &sightings);
    
private:
    std::vector<GameObject *> m_gameObjects;
};