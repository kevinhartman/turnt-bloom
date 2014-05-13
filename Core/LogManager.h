//
//  LogManager.h
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/28/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __Turnt_Bloom__LogManager__
#define __Turnt_Bloom__LogManager__

#include <iostream>

class LogManager {
    
private:
    LogManager() {};
    LogManager(LogManager const&);
    void operator=(LogManager const&);
    
public:
    static LogManager *getInstance()
    {
        static LogManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return &instance;
    }
    
public:
    bool init();
    void shutdown();
    
    static void error(std::string message);
    static void warn(std::string message);
    static void debug(std::string message);
    
};


#endif /* defined(__Turnt_Bloom__LogManager__) */
