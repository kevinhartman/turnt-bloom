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

#include "../Lua/LuaActorScript.h"

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
    
    /* create a new Actor using the loaded file */
    LuaActorScript *script = new LuaActorScript();
    Actor *actor = script->newInstance(lua);
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
    
    /* create a new Actor using the loaded file */
    LuaActorScript *script = new LuaActorScript();
    Actor *actor = script->newInstance(lua);
    assert(actor);
    
    /* Get Lua actor instance from Script */
    //assert(script->getLuaActor(lua, *actor));
    
}

void
TestLuaActorScript::test() {
    testActorCreate();
    testActorCreateAndReload();
}