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
        //std::cout << posA.x << std::endl;
        glm::vec3 posB = target->getWorldPos();
        //std::cout << posB.x << std::endl;
        float radA = this->getRadius();
        //std::cout << radA << std::endl
        float radB = target->getRadius();
        //std::cout << radB << std::endl
        //float minDistance =  radA + radB;
        //std::cout << minDistance << std::endl;
        //std::cout << glm::distance(posA, posB) << std::endl;

        return radA + radB > glm::distance(posA, posB);
    }

    glm::vec3 gravity;
    bool attached;
    bool active;
};
