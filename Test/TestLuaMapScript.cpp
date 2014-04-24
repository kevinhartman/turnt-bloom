//
//  TestLuaMapScript.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/21/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "TestLuaMapScript.h"
#include "../Lua/LuaGameMapScript.h"

void
TestLuaMapScript::test() {
    fprintf(stdout, "   Running Lua Map Script.\n");
    
    LuaGameMapScript *script = LuaGameMapScript::newInstance();
    
    assert(script);
    
    GameMap *map = script->createNewGameMap("game_maps/test_map.lua");
    
    assert(map);
    
}