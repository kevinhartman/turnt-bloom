//
//  TestUtils.h
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/28/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __Turnt_Bloom__TestUtils__
#define __Turnt_Bloom__TestUtils__

#include <iostream>

#include <lua.hpp>

class TestUtils {
public:
    static bool createLuaState(lua_State **lua);
};

#endif /* defined(__Turnt_Bloom__TestUtils__) */
