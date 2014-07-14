//
//  Map.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/18/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__Map__
#define __LuaProject__Map__

#include <iostream>
#include <vector>
#include <map>

#include "Actor.h"

class Map {
    
public:
    Map();
    
public:
    void computeInteractions(std::map<Actor *, std::vector<Actor *> *> &collisions,
                             std::map<Actor *, std::vector<Actor *> *> &sightings);
    bool addActor(Actor &actor);
    
private:
    std::vector<Actor *> m_actors;
};

#endif /* defined(__LuaProject__Map__) */