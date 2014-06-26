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

#include "GameActor.h"

class GameMap {
    
public:
    GameMap();
    
public:
    void updateScene(double timeElapsed);
    void computeInteractions(std::map<GameActor *, std::vector<GameActor *> *> &collisions,
                             std::map<GameActor *, std::vector<GameActor *> *> &sightings);
    bool addGameActor(GameActor &actor);
    
private:
    std::vector<GameActor *> m_gameActors;
};

#endif /* defined(__LuaProject__GameMap__) */