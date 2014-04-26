//
//  GameActor.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/17/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__GameActor__
#define __LuaProject__GameActor__

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

class GameActor {
    
public:
    GameActor();
    
public:
    bool isCollidingWith(GameActor &other);
    bool isSeeing(GameActor &other);
    
    void update(double timeElapsed);
    
private:
    std::vector<GameActor *> m_subscribers;
    
    /* motion */
    glm::vec3   m_position;
    glm::vec3   m_direction;
    float       m_speed;
    
    /* sight */
    glm::vec3   m_eyeline;
    float       m_fieldOfView;
    float       m_visionDepth;
    
    /* physics */
    float       m_bodyRadius;
};

#endif /* defined(__LuaProject__GameActor__) */
