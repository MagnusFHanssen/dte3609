#pragma once

#include "SceneObject.hpp"
#include "ColSphereBody.hpp"
#include "Model.hpp"
#include "Landscape.hpp"


class Rock : public SceneObject, public ColSphereBody
{
public:
    Rock(std::shared_ptr<Shader> shader, std::shared_ptr<Landscape> ls, std::shared_ptr<Model> model, bool falling = true);
    ~Rock();

    glm::vec3 getWorldPos() const;
    float getRadius() const;

    glm::vec3 gravity;
    bool attached;

    void setDamage(float damage);
    float collide();
    void respawn();

    void setPos(float x, float y, float z);

protected:
    void privateInit();
    void privateRender();
    void privateUpdate();

private:
    std::shared_ptr<Shader> shader_;
    std::shared_ptr<Landscape> ls_;
    std::shared_ptr<Model> model_;


    glm::vec3 worldPos;
    float scale_;

    float damage_;

    bool active_;
    bool falling_;

    glm::mat4 scaleRotMat_;

    // constants
    static const float MIN_X, MAX_X,
    MIN_Y, MAX_Y, MIN_Z, MAX_Z, MIN_SCALE, MAX_SCALE;

};

