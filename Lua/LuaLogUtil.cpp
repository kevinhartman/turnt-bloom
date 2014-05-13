//
//  LuaLogUtil.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/28/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LuaLogUtil.h"

#include "LogManager.h"

std::string
LuaLogUtil::dumpTable(lua_State *lua, int indent) {
    std::string tableDump = "Table:\n";
    
    if (indent > 10) {
        return "Too deep.\n";
    }
    
    if (!lua_istable(lua, -1)) {
        std::string message = "Can't table dump type: ";
        message += lua_typename(lua, -1);
        LogManager::error(message);
        
        return tableDump;
    }
    
    lua_pushnil(lua);
    while (lua_next(lua, -2) != 0) {
        
        /* add indent */
        for (int i = 0; i < indent; i++) {
            tableDump += "  ";
        }
        
        tableDump += "[";
        
        switch (lua_type(lua, -2)) {
            case LUA_TSTRING:
                tableDump += "\"";
                tableDump += lua_tostring(lua, -2);
                tableDump += "\"";
                break;
            case LUA_TNUMBER:
                tableDump += lua_tonumber(lua, -2);
                break;
            default:
                tableDump += lua_typename(lua, lua_type(lua, -2));
        }
        
        tableDump += "] = ";
        
        switch (lua_type(lua, -1)) {
            case LUA_TNONE:
            case LUA_TNIL:
            case LUA_TTHREAD:
            case LUA_TUSERDATA:
            case LUA_TFUNCTION:
            case LUA_TLIGHTUSERDATA:
                /* lazy for now */
                tableDump += lua_typename(lua, lua_type(lua, -1));
                break;
            case LUA_TNUMBER:
                tableDump += lua_tonumber(lua, -1);
                break;
            case LUA_TBOOLEAN:
                tableDump += (lua_toboolean(lua, -1) != 0);
                break;
            case LUA_TSTRING:
                tableDump += lua_tostring(lua, -1);
                break;
            case LUA_TTABLE:
                tableDump += dumpTable(lua, indent + 1);
                break;
            
            default:
                tableDump += "?";
                LogManager::error("Unknown lua type.");
                break;
        }
        
        tableDump += "\n";
        lua_pop(lua, 1); /* pop value */
    }
    //lua_pop(lua, 1); /* pop last key */
    
    return tableDump;
}