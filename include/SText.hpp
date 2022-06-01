#pragma once

#include <iostream>
#include <map>
#include <string>

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>

#include "Shader.hpp"

#include <../../glm-master/glm/glm.hpp>
#include <../../glm-master/glm/gtc/matrix_transform.hpp>
#include <../../glm-master/glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

struct SChar {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class SText
{
public:
    SText();

    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

    const unsigned int SCR_WIDTH = 900;
    const unsigned int SCR_HEIGHT = 700;

    std::map<GLchar, SChar> SChars;

    GLuint VAO, VBO;

    Shader shader_;
    glm::mat4 projection;


};
