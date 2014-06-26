//
//  SimulationManager.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/26/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "SimulationManager.h"
#include "Game.h"
#include "LuaScriptManager.h"

#include <assert.h>

void
SimulationManager::run() {
    /* game loop here */
    
    ScriptManager *scriptManager = LuaScriptManager::getInstance();

    Game *game;
    scriptManager->createGame(&game);

#ifdef DEBUG
    assert(game);
#endif
    
    
    while (true) {
        
    }
    
    for (int i = 0; i < 4; i++) {
        printf("Running iteration %d of game loop.\n", i);
    }
}