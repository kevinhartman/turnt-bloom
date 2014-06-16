//
//  TestLuaActorScript.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 5/14/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "TestLuaActorScript.h"

#include "TestUtils.h"
#include "LogManager.h"

#include "../Lua/LuaHelpers.h"
#include "../Lua/LuaLogUtil.h"

#include "../Lua/LuaGameActorScript.h"

static void *TEST_STACK = nullptr;

void
TestLuaActorScript::testActorCreate() {
    
    /* create a new lua state for this test */
    lua_State *lua = nullptr;
    assert(TestUtils::createLuaState(&lua));
    
    /* push value to ensure stack is as expected after call */
    lua_pushlightuserdata(lua, &TEST_STACK);
    
    /* load the test actor */
    assert(LuaHelpers::loadFile(lua, "game/actors/test_actor.lua"));
    
    /* print out the up value of loaded file */
    lua_getupvalue(lua, -1, 1);
    LogManager::debug(LuaLogUtil::dumpTable(lua));
    lua_pop(lua, 1);
    
    /* create a new GameActor using the loaded file */
    LuaGameActorScript *script = new LuaGameActorScript();
    GameActor *actor = script->createNewGameActor(lua);
    assert(actor);
    
    /* ensure stack is as expected */
    LogManager::debug(lua_typename(lua, lua_type(lua, -1)));
    LogManager::debug(LuaLogUtil::dumpTable(lua));
    
    assert(lua_touserdata(lua, -1) == &TEST_STACK);
}

void
TestLuaActorScript::testActorCreateAndReload() {
    
    /* create a new lua state for this test */
    lua_State *lua = nullptr;
    assert(TestUtils::createLuaState(&lua));
    
    /* load the test actor */
    assert(LuaHelpers::loadFile(lua, "game/actors/test_actor.lua"));
    
    /* create a new GameActor using the loaded file */
    LuaGameActorScript *script = new LuaGameActorScript();
    GameActor *actor = script->createNewGameActor(lua);
    assert(actor);
    
    /* Get Lua actor instance from Script */
    //assert(script->getLuaGameActor(lua, *actor));
    
}

void
TestLuaActorScript::test() {
    testActorCreate();
    testActorCreateAndReload();
}