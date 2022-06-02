# pragma once

#include <windows.h>
#include "SceneObject.hpp"

#include "Shader.hpp"

#include<string>
#include<vector>


class Skybox : public SceneObject
{
public:
    Skybox(std::shared_ptr<Shader> shader);

protected:
    void privateInit();
    void privateRender();
    void privateUpdate();
    GLuint loadCubemap(std::vector<std::string> faces);


private:
    std::shared_ptr<Shader> shader_;

    GLuint VBO_;
    GLuint VAO_;
    GLuint texture_;

};

