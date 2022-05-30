#pragma once

#include <windows.h>
#include "SceneObject.hpp"

class Minimap : public SceneObject
{
public:
    Minimap();
    ~Minimap();

    void startFB();
    void endFB();

protected:
    void privateInit();
    void privateRender();
    void privateUpdate();

private:
    GLuint frameBuffer_;
    GLuint textureColorBuffer_;
    GLuint renderBuffer_;

};

