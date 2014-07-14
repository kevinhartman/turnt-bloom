//
//  SimulationManager.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/26/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "SimulationManager.h"
#include "ScriptManager.h"
#include "GameScript.h"
#include "Game.h"

#include <assert.h>
#include <vector>
#include <map>

const char* const GAME_FILE = "game/test_game.lua";

void
SimulationManager::updateScene(double timeElapsed, Map *map) {
    // TODO: this could be done better. maybe (N/D)^2, where D is cell divisions of map
    
    std::map<Actor *, std::vector<Actor *> *> collisions;
    std::map<Actor *, std::vector<Actor *> *> sightings;
    
    map->computeInteractions(collisions, sightings);
    
    std::map<Actor *, std::vector<Actor *> *>::iterator iter;
    
    /* call game actor script with collision data */
    for (iter = collisions.begin(); iter != collisions.end(); ++iter) {
        
        Actor *actor = iter->first;
        
        // TODO: call script collision callback with iter->second
        
    }
    
    /* call game actor script with sighting data */
    for (iter = sightings.begin(); iter != sightings.end(); ++iter) {
        
        Actor *actor = iter->first;
        
        // TODO: call script sightings callback with iter->second
        
    }
    
}

void
SimulationManager::run() {
    /* game loop here */
    
    ScriptManager *scriptManager = ScriptManager::getInstance();

    GameScript *gameScript = scriptManager->newGameScript();
    
    Game *game = gameScript->createNewGame(GAME_FILE);

#ifdef DEBUG
    assert(game);
#endif
    
    
    while (true) {
        
    }
    
    for (int i = 0; i < 4; i++) {
        printf("Running iteration %d of game loop.\n", i);
    }
}