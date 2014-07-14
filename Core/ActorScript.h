//
//  ActorScript.h
//  Turnt Bloom
//
//  Created by Kevin Hartman on 7/8/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef Turnt_Bloom_ActorScript_h
#define Turnt_Bloom_ActorScript_h

#include "Actor.h"

class ActorScript {
    
public:
    virtual Actor * createNewActor(std::string filePath) = 0;
    
};


#endif
