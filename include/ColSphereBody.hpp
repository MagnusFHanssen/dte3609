#pragma once

#include <windows.h>
#include <iostream>

//#include "SceneObject.hpp"
#include "../../glm-master/glm/glm.hpp"

class ColSphereBody
{
public:
    virtual glm::vec3 getWorldPos() const = 0;
    virtual float getRadius() const = 0;

    bool detectCollision(ColSphereBody* target) const{
        if(!target->active)
            return false;
        glm::vec3 posA = this->getWorldPos();
        glm::vec3 posB = target->getWorldPos();
        float radA = this->getRadius();
        float radB = target->getRadius();

        return radA + radB > glm::distance(posA, posB);
    }

    glm::vec3 gravity;
    bool attached;
    bool active;
};
