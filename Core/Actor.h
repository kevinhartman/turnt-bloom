//
//  Actor.h
//  LuaProject
//
//  Created by Kevin Hartman on 4/17/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#ifndef __LuaProject__Actor__
#define __LuaProject__Actor__

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

class Actor {
    
public:
    Actor();
    
public:
    bool isCollidingWith(Actor &other);
    bool isSeeing(Actor &other);
    
    void update(double timeElapsed);
    
public:
    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);
    
    glm::vec3 getEyeline();
    void setEyeline(glm::vec3 eyeline);
    
    float getFieldOfView();
    void setFieldOfView(float fOV);
    
    float getVisionDepth();
    void setVisionDepth(float visionDepth);
    
    float getBodyRadius();
    void setBodyRadius(float bodyRadius);
    
    
private:
    std::vector<Actor *> m_subscribers;
    
    /* motion */
    glm::vec3   m_position;
    
    /* sight */
    glm::vec3   m_eyeline;
    float       m_fieldOfView;
    float       m_visionDepth;
    
    /* physics */
    float       m_bodyRadius;
    
    /* model */
    std::vector<glm::vec4> m_verticies;
};

#endif /* defined(__LuaProject__Actor__) */
