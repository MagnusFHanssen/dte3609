#pragma once

#include <windows.h>

//#include "SceneObject.hpp"
#include "../../glm-master/glm/glm.hpp"

class ColSphereBody
{
public:
    virtual glm::vec3 getWorldPos() const = 0;
    virtual float getRadius() const = 0;

    bool detectCollision(ColSphereBody* target) const{
        glm::vec3 posA = this->getWorldPos();
        glm::vec3 posB = target->getWorldPos();
        float minDistance = this->getRadius() + target->getRadius();

        return minDistance < glm::distance(posA, posB);
    }

    glm::vec3 gravity;
    bool attached;
};
