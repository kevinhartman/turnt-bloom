//
//  GameScript.h
//  Turnt Bloom
//
//  Created by Kevin Hartman on 7/8/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef Turnt_Bloom_GameScript_h
#define Turnt_Bloom_GameScript_h

#include "Game.h"

class GameScript {
    
public:
    virtual Game * createNewGame(std::string filePath) = 0;
    
};

#endif
