#pragma once

#include <windows.h>
#include "SceneObject.hpp"

#include <string>

#include "../../glm-master/glm/gtc/matrix_transform.hpp"



// Character types:
int const STROKE_CHAR = 0;
int const BITMAP_CHAR = 1;

class Text : public SceneObject
{
public:
    Text(std::string string, glm::vec3 pos, void* font, int type, glm::vec3 color);

    void strokeCharacter();
    void bitmapCharacter();
    void setString(std::string string);

protected:
    void privateInit();
    void privateRender();
    void privateUpdate();

private:
    glm::vec3 pos_;
    void* font_;
    std::string string_;
    int type_;
    glm::vec3 color_;
};

