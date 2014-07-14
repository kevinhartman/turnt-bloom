//
//  Actor.cpp
//  LuaProject
//
//  Created by Kevin Hartman on 4/17/14.
//  Copyright (c) 2014 Kevin Hartman. All rights reserved.
//

#include "Actor.h"
#include <glm/gtx/norm.hpp>
#include <glm/gtx/vector_angle.hpp>

Actor::Actor() :

    m_subscribers(),

    m_position(0.0f, 0.0f, 0.0f),

    m_eyeline(0.0f, 0.0f, 0.0f),
    m_fieldOfView(0.0f),
    m_visionDepth(0.0f),
    
    m_bodyRadius(0.0f),

    m_verticies()
{}

glm::vec3
Actor::getPosition() {
    return m_position;
}

void
Actor::setPosition(glm::vec3 position) {
    m_position = position;
}

glm::vec3
Actor::getEyeline() {
    return m_eyeline;
}

void
Actor::setEyeline(glm::vec3 eyeline) {
    m_eyeline = eyeline;
}

float
Actor::getFieldOfView() {
    return m_fieldOfView;
}

void
Actor::setFieldOfView(float fOV) {
    m_fieldOfView = fOV;
}

float
Actor::getVisionDepth() {
    return m_visionDepth;
}

void
Actor::setVisionDepth(float visionDepth) {
    m_visionDepth = visionDepth;
}

float
Actor::getBodyRadius() {
    return m_bodyRadius;
}

void
Actor::setBodyRadius(float bodyRadius) {
    m_bodyRadius = bodyRadius;
}

bool
Actor::isCollidingWith(Actor &other) {
    
    float distance2 = glm::distance2(m_position, other.m_position);
    float radiiSum2 = glm::pow((m_bodyRadius + other.m_bodyRadius), 2.0f);
                               
    return distance2 < radiiSum2;
}

bool
Actor::isSeeing(Actor &other) {
    
    // TODO: only detects if position of other is in view.
    // this should be expanded to see if other's physics body is in field of view
    float distance2 = glm::distance2(m_position, other.m_position);
    float visionDepth2 = glm::pow(m_visionDepth, 2.0f);
    
    /* test if too far away */
    if (distance2 > visionDepth2) {
        return false;
    }
    
    /* test if inside viewing angle */
    glm::vec3 directionToOther = other.m_position - m_position;
    float angleFromEyeline = glm::angle(m_eyeline, directionToOther);
    
    return angleFromEyeline < (m_fieldOfView / 2);
}
