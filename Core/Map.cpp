//
//  Map.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/18/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "Map.h"

Map::Map() : m_actors() {
    // TODO: put some test game actors in here for script project
}

bool
Map::addActor(Actor &actor) {
    m_actors.push_back(&actor);
    return true;
}

void
Map::computeInteractions(std::map<Actor *, std::vector<Actor *> *> &collisions,
                             std::map<Actor *, std::vector<Actor *> *> &sightings) {
    
    for (int i = 0; i < m_actors.size(); i++) {
        
        Actor *actor = m_actors.at(i);
        
        /* initialize lists of interactions for this actor */
        collisions[actor] = new std::vector<Actor *>();
        sightings[actor] = new std::vector<Actor *>();
        
        for (Actor *anotherActor : m_actors) {
            
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
                             

