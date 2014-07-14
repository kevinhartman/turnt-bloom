//
//  Engine.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/26/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LogManager.h"
#include "LuaScriptManager.h"
#include "SimulationManager.h"

LogManager *g_logManager = LogManager::getInstance();
SimulationManager *g_simulationManager = SimulationManager::getInstance();
ScriptManager *g_scriptManager = LuaScriptManager::getInstance();

int main(int argc, char* argv[])
{
    fprintf(stdout, "Engine started.\n");
    
    // TODO:
    // initialize subsystems here
    g_logManager->init(/* log file path */);
    g_scriptManager->init(GAME_FILE);
    
    // TODO: Pass control to GameManager here
    // simulation manager.run()
    g_simulationManager->run();
    
    // TODO:
    // shutdown subsystems here
    g_scriptManager->shutdown();
    g_logManager->shutdown();
    
	return 0;
}