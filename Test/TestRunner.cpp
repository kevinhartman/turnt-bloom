//
//  TestRunner.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/21/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include <iostream>

#include "TestLuaMapScript.h"
#include "TestLuaLogUtil.h"
#include "TestLuaActorScript.h"

#include "LogManager.h"

static void (*TESTS[])() =
{
    TestLuaMapScript::test,
    TestLuaActorScript::test,
    TestLuaLogUtil::test,
    nullptr /* sentinal */
};

int main(int argc, char* argv[])
{
    
    fprintf(stdout, "TESTS RUNNING.\n");
    
    /* initialize logger */
    LogManager::getInstance()->init();
    
    int testIndex = 0;
    
    while (TESTS[testIndex]) {
        TESTS[testIndex++]();
    }
    
    LogManager::getInstance()->shutdown();
    
	return 0;
}