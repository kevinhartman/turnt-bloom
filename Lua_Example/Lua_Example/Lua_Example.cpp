// Lua_Example.cpp : Defines the entry point for the console application.
//

#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

int main(int argc, char* argv[])
{
    lua_State *L = luaL_newstate();
    
    // load Lua libraries
    static const luaL_Reg lualibs[] =
    {
        { "base", luaopen_base },
        { "io", luaopen_io },
        { NULL, NULL}
    };
    
    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        lib->func(L);
        lua_settop(L, 0);
    }
    
    // run the Lua script
    luaL_dofile(L, "game_objects/helloworld.lua");
    
    // close the Lua state
    lua_close(L);
    
    
    
	return 0;
}

