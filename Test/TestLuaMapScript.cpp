//
//  TestLuaMapScript.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/21/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "TestUtils.h"
#include "LogManager.h"

#include "TestLuaMapScript.h"
#include "../Lua/LuaGameMapScript.h"
#include "../Lua/LuaHelpers.h"
#include "../Lua/LuaLogUtil.h"

static void *TEST_STACK = nullptr;

void
TestLuaMapScript::test() {
    
    LogManager::debug("Running TestLuaMapScript.cpp");
    
    /* create a new lua state for this test */
    lua_State *lua = nullptr;
    assert(TestUtils::createLuaState(&lua));
    
    /* push value to ensure stack is as expected after call */
    lua_pushlightuserdata(lua, &TEST_STACK);
    
    /* load the test map */
    assert(LuaHelpers::loadFile(lua, "game/game_maps/test_map.lua"));

    /* printf out the up value of loaded file */
    lua_getupvalue(lua, -1, 1);
    LogManager::debug(LuaLogUtil::dumpTable(lua));
    lua_pop(lua, 1);
    
    /* create a new GameMap using the loaded file */
    LuaGameMapScript *script = new LuaGameMapScript();
    GameMap *map = script->createNewGameMap(lua);
    assert(map);
    
    /* ensure stack is as expected */
    LogManager::debug(lua_typename(lua, lua_type(lua, -1)));
    LogManager::debug(LuaLogUtil::dumpTable(lua));
    
    assert(lua_touserdata(lua, -1) == &TEST_STACK);
    
}