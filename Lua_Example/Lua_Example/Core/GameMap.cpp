//
//  GameMap.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/18/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "GameMap.h"

GameMap::GameMap() : m_gameObjects() {
    // TODO: put some test game objects in here for script project
}

void
GameMap::computeInteractions(std::map<GameObject *, std::vector<GameObject *> *> &collisions,
                             std::map<GameObject *, std::vector<GameObject *> *> &sightings) {
    
    for (int i = 0; i < m_gameObjects.size(); i++) {
        
        GameObject *object = m_gameObjects.at(i);
        
        /* initialize lists of interactions for this object */
        collisions[object] = new std::vector<GameObject *>();
        sightings[object] = new std::vector<GameObject *>();
        
        for (GameObject *anotherObject : m_gameObjects) {
            
            /* skip self */
            if (object == anotherObject) {
                continue;
            }
            
            /* update collisions */
            if (object->isCollidingWith(*anotherObject)) {
                
                collisions[object]->push_back(anotherObject);
            }
            
            /* update sightings */
            if (object->isSeeing(*anotherObject)) {
                
                sightings[object]->push_back(anotherObject);
            }
        }
    }
}
                             

void
GameMap::updateScene(double timeElapsed) {
    // TODO: this could be done better. maybe (N/D)^2, where D is cell divisions of map
    
    std::map<GameObject *, std::vector<GameObject *> *> collisions;
    std::map<GameObject *, std::vector<GameObject *> *> sightings;
    
    computeInteractions(collisions, sightings);
    
    std::map<GameObject *, std::vector<GameObject *> *>::iterator iter;
    
    /* call game object script with collision data */
    for (iter = collisions.begin(); iter != collisions.end(); ++iter) {
        
        GameObject *object = iter->first;
        
        // TODO: call script collision callback with iter->second
        
    }
    
    /* call game object script with sighting data */
    for (iter = sightings.begin(); iter != sightings.end(); ++iter) {
        
        GameObject *object = iter->first;
        
        // TODO: call script sightings callback with iter->second
        
    }
    
}