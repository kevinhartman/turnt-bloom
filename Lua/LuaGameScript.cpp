//
//  LuaGameScript.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 6/16/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include <assert.h>
#include "LuaGameScript.h"
#include "LuaHelpers.h"
#include "LogManager.h"
#include "LuaLogUtil.h"

#include <lauxlib.h>
#include <lualib.h>

LuaGameScript::LuaGameScript() {}

bool
LuaGameScript::initializeGame(lua_State *lua, Game &game) {
    
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
    
    return true;
    
}

/*
 * Creates a new Game using the function at the top of the lua stack.
 *
 * Pops the function at the top of the stack before returning.
 */
Game *
LuaGameScript::createNewGame(lua_State *lua) {
    
    if (!lua_isfunction(lua, -1)) {
        fprintf(stderr, "** Error: A game function must be present on the top of the stack to create a new game.\n");
        return nullptr;
    }
    
    /* create a game */
    Game *game = new Game();
    
    /* duplicate function so we can read the loaded environment after running */
    lua_pushvalue(lua, -1);
    
    /* load the game into its environment.
     * Note: anything preloaded in its _ENV will be overwritten
     *       if there's a naming conflict.
     */
    if (!LuaHelpers::runFunction(lua)) {
        /* remove the game function */
        lua_pop(lua, 1);
        return nullptr;    }
    
    if (!initializeGame(lua, *game)) {
        /* remove the game function */
        lua_pop(lua, 1);
        return nullptr;
    }
    
    /* store the game's instance so we can get it later */
    lua_pushlightuserdata(lua, (void *)game);    /* push game address */
    lua_pushvalue(lua, -2);                     /* push game function */
    
    /* registry[&game] = game function instance */
    lua_settable(lua, LUA_REGISTRYINDEX);
    
    /* remove the game function from the stack before returning */
    lua_pop(lua, 1);
    
    return game;
}