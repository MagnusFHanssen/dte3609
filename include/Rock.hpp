#pragma once

#include "SceneObject.hpp"
#include "ColSphereBody.hpp"
#include "Model.hpp"
#include "Landscape.hpp"


class Rock : public SceneObject, public ColSphereBody
{
public:
    Rock(std::shared_ptr<Shader> shader, std::shared_ptr<Landscape> ls, std::shared_ptr<Model> model);
    ~Rock();

    glm::vec3 getWorldPos();
    float getRadius();

    glm::vec3 gravity;
    bool attached;


    float collide();
    void respawn();

protected:
    void privateInit();
    void privateRender();
    void privateUpdate();

private:
    std::shared_ptr<Shader> shader_;
    std::shared_ptr<Landscape> ls_;
    std::shared_ptr<Model> model_;


    glm::vec3 worldPos;

    std::random_device rd;

    float damage_;

};

