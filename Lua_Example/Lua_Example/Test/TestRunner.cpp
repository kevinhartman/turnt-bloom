//
//  TestRunner.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/21/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include <iostream>

#include "TestLuaMapScript.h"


static void (*TESTS[])() =
{
    TestLuaMapScript::test,
    nullptr /* sentinal */
};

int main(int argc, char* argv[])
{
    
    fprintf(stdout, "TESTS RUNNING.\n");
    
    int testIndex = 0;
    
    while (TESTS[testIndex]) {
        TESTS[testIndex++]();
    }
    
	return 0;
}