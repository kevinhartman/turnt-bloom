//
//  MapScript.h
//  Turnt Bloom
//
//  Created by Kevin Hartman on 7/8/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef Turnt_Bloom_MapScript_h
#define Turnt_Bloom_MapScript_h

#include "Map.h"

class MapScript {
    
public:
    virtual Map * createNewMap(std::string filePath) = 0;
    
};


#endif
