//
//  TestLuaLogUtil.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/28/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//


#include "TestLuaLogUtil.h"

#include "LogManager.h"
#include "TestUtils.h"
#include "../Lua/LuaLogUtil.h"

#include <lua.hpp>

#include <assert.h>

void
TestLuaLogUtil::test() {
    fprintf(stdout, "   Running TestLuaLogUtil test.\n");
    
    lua_State *lua = nullptr;
    assert(TestUtils::createLuaState(&lua));

    
    lua_newtable(lua);
    lua_pushstring(lua, "Test key.");
    lua_pushstring(lua, "Test value.");
    lua_settable(lua, -3);
    
    LogManager::debug(lua_typename(lua, lua_type(lua, -1)));
    LogManager::debug(LuaLogUtil::dumpTable(lua));
    
    LogManager::debug(lua_typename(lua, lua_type(lua, -1)));
    
    LogManager::debug(LuaLogUtil::dumpTable(lua));

}