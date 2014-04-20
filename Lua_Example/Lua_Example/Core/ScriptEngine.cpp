//
//  ScriptEngine.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/17/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include <lauxlib.h>
#include <lualib.h>

#include "ScriptEngine.h"

ScriptEngine::ScriptEngine() {}

void
ScriptEngine::updateScene(GameMap &map, double timeElapsed) {
    // TODO: this could be done better. maybe (N/D)^2, where D is cell divisions of map
    
    std::map<GameObject *, std::vector<GameObject *> *> collisions;
    std::map<GameObject *, std::vector<GameObject *> *> sightings;
    
    map.computeInteractions(collisions, sightings);
    
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