//
//  ScriptManager.h
//  Project
//
//  Created by Kevin Hartman on 4/17/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __Turnt_Bloom__ScriptManager__
#define __Turnt_Bloom__ScriptManager__

#include "Game.h"
#include "GameScript.h"
#include "MapScript.h"
#include "ActorScript.h"

#include <iostream>


class ScriptManager {
    
private:
    ScriptManager() {};
    ScriptManager(ScriptManager const&);
    void operator=(ScriptManager const&);
    
public:
    static ScriptManager *getInstance()
    {
        static ScriptManager instance;
        
        return &instance;
    }
    
public:
    bool init();
    void shutdown();
    
public:
    GameScript *    newGameScript();
    MapScript *     newMapScript();
    ActorScript *   newActorScript();
    
};


#endif /* defined(__Turnt_Bloom__ScriptManager__) */
