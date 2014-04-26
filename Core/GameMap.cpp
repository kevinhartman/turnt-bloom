//
//  GameMap.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/18/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "GameMap.h"

GameMap::GameMap() : m_gameActors() {
    // TODO: put some test game actors in here for script project
}

void
GameMap::computeInteractions(std::map<GameActor *, std::vector<GameActor *> *> &collisions,
                             std::map<GameActor *, std::vector<GameActor *> *> &sightings) {
    
    for (int i = 0; i < m_gameActors.size(); i++) {
        
        GameActor *actor = m_gameActors.at(i);
        
        /* initialize lists of interactions for this actor */
        collisions[actor] = new std::vector<GameActor *>();
        sightings[actor] = new std::vector<GameActor *>();
        
        for (GameActor *anotherActor : m_gameActors) {
            
            /* skip self */
            if (actor == anotherActor) {
                continue;
            }
            
            /* update collisions */
            if (actor->isCollidingWith(*anotherActor)) {
                
                collisions[actor]->push_back(anotherActor);
            }
            
            /* update sightings */
            if (actor->isSeeing(*anotherActor)) {
                
                sightings[actor]->push_back(anotherActor);
            }
        }
    }
}
                             

void
GameMap::updateScene(double timeElapsed) {
    // TODO: this could be done better. maybe (N/D)^2, where D is cell divisions of map
    
    std::map<GameActor *, std::vector<GameActor *> *> collisions;
    std::map<GameActor *, std::vector<GameActor *> *> sightings;
    
    computeInteractions(collisions, sightings);
    
    std::map<GameActor *, std::vector<GameActor *> *>::iterator iter;
    
    /* call game actor script with collision data */
    for (iter = collisions.begin(); iter != collisions.end(); ++iter) {
        
        GameActor *actor = iter->first;
        
        // TODO: call script collision callback with iter->second
        
    }
    
    /* call game actor script with sighting data */
    for (iter = sightings.begin(); iter != sightings.end(); ++iter) {
        
        GameActor *actor = iter->first;
        
        // TODO: call script sightings callback with iter->second
        
    }
    
}