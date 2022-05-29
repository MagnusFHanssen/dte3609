#pragma once

#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#include "../../glm-master/glm/gtc/matrix_transform.hpp"

#include "SceneObject.hpp"
#include "Camera.hpp"

#include <string>

typedef struct
{
    bool active;
    float life;
    float fade;
    float x, y, z;
    float x_v, y_v, z_v;
    float x_a, y_a, z_a;

}
part;

class Particle : public SceneObject
{
public:
    Particle();
    Particle(glm::vec3 pos, glm::vec3 fall);
    ~Particle();

protected:
    void privateInit();
    void privateUpdate();
    void privateRender();

private:
    bool loadTexture();
    void particleInit(GLuint loop);
    void draw();
    void initVariables();

#define MAX_PARTICLES 500
    part particles[MAX_PARTICLES];
    GLuint loop_;
    GLuint texName_;
    bool texLoaded_;

    glm::vec3 pos_;
    glm::vec3 fall_;
    glm::vec3 slow_;

    float size_;
    float life_;
    float zoom_;
};

