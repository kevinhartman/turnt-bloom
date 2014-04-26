//
//  Engine.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/26/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaScriptManager.h"
#include "SimulationManager.h"


SimulationManager *g_simulationManager = SimulationManager::getInstance();
ScriptManager *g_scriptManager = LuaScriptManager::getInstance();

int main(int argc, char* argv[])
{
    fprintf(stdout, "Engine started.\n");
    
    // TODO:
    // initialize subsystems here
    // scriptmanager.init(script_type=LUA, gamescript=path)
    g_scriptManager->init();
    
    // TODO: Pass control to GameManager here
    // simulation manager.run()
    g_simulationManager->run();
    
    // TODO:
    // shutdown subsystems here
    g_scriptManager->shutdown();
    
	return 0;
}