#pragma once

#include <windows.h>
#include "SceneObject.hpp"
#include "Camera.hpp"


class Billboard : public SceneObject
{
public:
    Billboard();
    Billboard(GLfloat width, GLfloat height, glm::vec3 startPos,
              std::shared_ptr<SceneObject> obj, std::shared_ptr<Camera> cam);
    ~Billboard();

protected:
    void privateInit();
    void privateRender();
    void privateUpdate();

    std::shared_ptr<SceneObject> obj_;
    std::shared_ptr<Camera> cam_;

private:
    GLfloat width_;
    GLfloat height_;
    glm::vec3 startPos_;

    GLuint drawList_;
};

