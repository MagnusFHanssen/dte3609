#include "../include/Landscape.hpp"
#include "../include/stb_image.h"

Landscape::Landscape(float initialDistance) : distance(initialDistance)
{
}

Landscape::~Landscape()
{
}

void Landscape::privateInit()
{
    width = 40.0f;
    length = 60.0f;
    rise_ = 5.0f;

    int texScaleFactor = 5;

    auto const frac = length/3.0f;

    texLoaded_ = loadTextures();

  // Create vertex arrays
    vertexArray_ = {{-width/2.0f, 0.0f, -frac},
                  {-width/2.0f, 0.0f, 0.0f},
                  {width/2.0f, 0.0f, 0.0f},
                  {width/2.0f, 0.0f, -frac},

                  {-width/2.0f, rise_, -2*frac},
                  {-width/2.0f, 0.0f, -frac},
                  {width/2.0f, 0.0f, -frac},
                  {width/2.0f, rise_, -2*frac},

                  {-width/2.0f, 0.0f, -length},
                  {-width/2.0f, rise_, -2*frac},
                  {width/2.0f, rise_, -2*frac},
                  {width/2.0f, 0.0f, -length}};

    for (auto vec : vertexArray_){
        texCoordArray_.emplace_back(glm::vec2(vec.x/texScaleFactor, vec.z/texScaleFactor));
    }
}

void Landscape::privateRender()
{
  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0.0f, 0.0f, distance);


  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texName_);

  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  glColor3f(1.0f, 1.0f, 1.0f);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertexArray_.front().x);

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT, 0, &texCoordArray_.front().s);


  glEnable(GL_AUTO_NORMAL);
  glDrawArrays(GL_QUADS, 0, 12);
  glDisable(GL_AUTO_NORMAL);


  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glBindTexture(GL_TEXTURE_2D, NULL);
  glDisable(GL_TEXTURE_2D);

  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
}

void Landscape::privateUpdate()
{
    //distance += 0.01f;
    if (distance >= length * 2){
        distance -= length * 3;
    }
}

bool Landscape::loadTextures()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName_);

    glBindTexture(GL_TEXTURE_2D, texName_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("./resources/textures/rock.jpg", &width, &height, &nrChannels, 0);

    if(data)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else
        return false;

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, NULL);

    return true;
}

