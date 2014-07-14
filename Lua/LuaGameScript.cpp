//
//  LuaGameScript.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 6/16/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include <assert.h>
#include "LuaGameScript.h"
#include "LogManager.h"
#include "LuaLogUtil.h"
#include "LuaStateManager.h"

#include <lauxlib.h>
#include <lualib.h>

LuaGameScript::LuaGameScript() {}

Game *
LuaGameScript::createNewGame(std::string filePath) {
    
    lua_State *lua = LuaStateManager::getLuaState();
    
    // TODO: set stack to empty?
    
    /* load the game from script */
    if (!LuaHelpers::loadFile(lua, filePath)) {
        // TODO: is cleanup required on fail?
        return nullptr;
    }
    
#ifdef DEBUG
    /* print out the up value of loaded file */
    lua_getupvalue(lua, -1, 1);
    LogManager::debug(LuaLogUtil::dumpTable(lua));
    lua_pop(lua, 1);
#endif
    
    return newInstance(lua);
}

Game *
LuaGameScript::initialize(lua_State *lua) {
    
    Game *game = new Game();
    
    /* get game's _ENV */
    lua_getupvalue(lua, -1, 1);
    
#ifdef DEBUG
    assert(lua_istable(lua, -1));
    LogManager::debug(LuaLogUtil::dumpTable(lua));
#endif
    
    // TODO: read game here
    
    
    lua_pop(lua, 1);    /* remove the _ENV table */
    
#ifdef DEBUG
    /* ensure we're back to the function we were called with */
    //LogManager::debug(LuaLogUtil::dumpTable(lua));
    LogManager::debug(lua_typename(lua, lua_type(lua, -1)));
    assert(lua_isfunction(lua, -1));
#endif
    
    return game;
    
}