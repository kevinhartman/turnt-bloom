// Lua_Example.cpp : Defines the entry point for the console application.
//
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

int main(int argc, char* argv[])
{
	lua_State *L;
	luaL_openlibs(L); 
	lua_close(L);
	return 0;
}

