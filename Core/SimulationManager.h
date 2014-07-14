//
//  SimulationManager.h
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/26/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __Turnt_Bloom__SimulationManager__
#define __Turnt_Bloom__SimulationManager__

#include <iostream>

#include "Map.h"

class SimulationManager {
    
private:
    SimulationManager() {};
    SimulationManager(SimulationManager const&);
    void operator=(SimulationManager const&);
    
public:
    static SimulationManager *getInstance()
    {
        static SimulationManager instance;
        
        return &instance;
    }
    
public:
    void run();
    
private:
    void updateScene(double timeElapsed, Map *map);

};

#endif /* defined(__Turnt_Bloom__SimulationManager__) */
