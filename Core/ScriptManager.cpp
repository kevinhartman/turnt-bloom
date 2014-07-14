//
//  ScriptManager.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 7/8/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "ScriptManager.h"

#include "LuaGameScript.h"
#include "LuaMapScript.h"
#include "LuaActorScript.h"

bool
ScriptManager::init() {
    //TODO: stubbed
    return true;
}

void
ScriptManager::shutdown() {
    
}

GameScript *
ScriptManager::newGameScript() {
    return new LuaGameScript();
}

MapScript *
ScriptManager::newMapScript() {
    return new LuaMapScript();
}

ActorScript *
ScriptManager::newActorScript() {
    return new LuaActorScript();
}