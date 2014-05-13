//
//  LogManager.cpp
//  Turnt Bloom
//
//  Created by Kevin Hartman on 4/28/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "LogManager.h"

bool
LogManager::init() {
    return true;
}

void
LogManager::shutdown() {
    
}

void
LogManager::error(std::string message) {
    // TODO: get file from instance
    fprintf(stderr, "** Error: %s\n", message.c_str());
    fflush(stderr);
}

void
LogManager::warn(std::string message) {
    fprintf(stderr, "* Warning: %s\n", message.c_str());
    fflush(stderr);
}

void
LogManager::debug(std::string message) {
    fprintf(stdout, "%s\n", message.c_str());
    fflush(stdout);
}