//
//  LuaActorScript.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/19/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaActorScript.h"
#include "LogManager.h"
#include "LuaLogUtil.h"
#include "LuaStateManager.h"

#include <lauxlib.h>
#include <lualib.h>

const char* const GLOBAL_POSITION =         "position";
const char* const GLOBAL_DIRECTION =        "direction";
const char* const GLOBAL_SPEED =            "speed";
const char* const GLOBAL_EYELINE =          "eyeline";
const char* const GLOBAL_FIELD_OF_VIEW =    "fieldOfView";
const char* const GLOBAL_VISION_DEPTH =     "visionDepth";
const char* const GLOBAL_BODY_RADIUS =      "bodyRadius";


LuaActorScript::LuaActorScript() {}

Actor *
LuaActorScript::createNewActor(std::string filePath) {
    
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

Actor *
LuaActorScript::initialize(lua_State *lua) {
    
    Actor *actor = new Actor();
    
    /* get map's _ENV */
    lua_getupvalue(lua, -1, 1);
    
#ifdef DEBUG
    assert(lua_istable(lua, -1));
    LogManager::debug(LuaLogUtil::dumpTable(lua));
#endif
    
    /* Get position */
    lua_getfield(lua, -1, GLOBAL_POSITION);

    lua_Number position[3];
    if (!LuaHelpers::getVec3(lua, position)) {
        LogManager::error("Position is invalid or missing.");
        
        lua_pop(lua, 1); /* remove invalid position */
        lua_pop(lua, 1); /* remove _ENV */
        return nullptr;
    }
    
    actor->setPosition(glm::vec3(position[0], position[1], position[2]));

    lua_pop(lua, 1); /* remove position */

    /* Get eyeline */
    lua_getfield(lua, -1, GLOBAL_EYELINE);
    
    lua_Number eyeline[3];
    if (!LuaHelpers::getVec3(lua, eyeline)) {
        LogManager::error("Eyeline is invalid or missing.");
        
        lua_pop(lua, 1); /* remove invalid eyeline */
        lua_pop(lua, 1); /* remove _ENV */
        return nullptr;
    }
    
    actor->setEyeline(glm::vec3(eyeline[0], eyeline[1], eyeline[2]));
    
    lua_pop(lua, 1); /* remove eyeline */
    
    /* Get field of view */
    lua_getfield(lua, -1, GLOBAL_FIELD_OF_VIEW);
    
    if (!lua_isnumber(lua, -1)) {
        LogManager::error("Eyeline is invalid or missing.");
        
        lua_pop(lua, 1); /* remove invalid FOV */
        lua_pop(lua, 1); /* remove _ENV */
        return nullptr;
    }
    
    lua_Number fieldOfView = lua_tonumber(lua, -1);
    actor->setFieldOfView(fieldOfView);
    
    lua_pop(lua, 1); /* remove FOV */
    
    /* Get vision depth */
    lua_getfield(lua, -1, GLOBAL_VISION_DEPTH);
    
    if (!lua_isnumber(lua, -1)) {
        LogManager::error("Vision depth is invalid or missing.");
        
        lua_pop(lua, 1); /* remove invalid vision depth */
        lua_pop(lua, 1); /* remove _ENV */
        return nullptr;
    }
    
    lua_Number visionDepth = lua_tonumber(lua, -1);
    actor->setVisionDepth(visionDepth);
    
    lua_pop(lua, 1); /* remove vision depth */

    /* Get body radius */
    lua_getfield(lua, -1, GLOBAL_BODY_RADIUS);
    
    if (!lua_isnumber(lua, -1)) {
        LogManager::error("Body radius is invalid or missing.");
        
        lua_pop(lua, 1); /* remove invalid body radius */
        lua_pop(lua, 1); /* remove _ENV */
        return nullptr;
    }
    
    lua_Number bodyRadius = lua_tonumber(lua, -1);
    actor->setBodyRadius(bodyRadius);
    
    lua_pop(lua, 1);    /* remove body radius */
    lua_pop(lua, 1);    /* remove the _ENV table */
    
#ifdef DEBUG
    /* ensure we're back to the function we were called with */
    assert(lua_isfunction(lua, -1));
#endif
    
    return actor;
}

void
LuaActorScript::onError(Actor *actor, int errorCode) {
    // TODO: stubbed
    return;
}

bool
LuaActorScript::onCollide(Actor *actor, Actor *other) {
    // TODO: stubbed
    return false;
}

bool
LuaActorScript::onSight(Actor *actor, Actor *other) {
    // TODO: stubbed
    return false;
}

bool
LuaActorScript::onTargetUpdate(Actor *actor, Actor *other) {
    // TODO: stubbed
    return false;
}

void
LuaActorScript::onKeyboard(Actor *actor) {
    // TODO: stubbed
    return;
}