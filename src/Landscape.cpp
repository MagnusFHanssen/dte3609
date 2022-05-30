#include "../include/Landscape.hpp"
#include "../include/stb_image.h"
#include "../../glm-master/glm/gtc/matrix_transform.hpp"

#include <cmath>


Landscape::Landscape(float initialDistance, int repeats) : distance(initialDistance), repeats_{repeats}
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

    matrix_ = glm::translate(matrix_, {0.0f, 0.0f, distance});
}

void Landscape::privateRender()
{
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

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0f, 1.0f);
  glEnable(GL_AUTO_NORMAL);

  auto old_matrix = matrix_;
  matrix_ = glm::translate(matrix_, {0.0f, 0.0f, -length});

  //for (int i = 0; i < repeats_; i++){
      glDrawArrays(GL_QUADS, 0, 12);
  //    matrix_ = glm::translate(matrix_, {0.0f, 0.0f, length});
  //}
  matrix_ = old_matrix;

  glDisable(GL_AUTO_NORMAL);

  glBindTexture(GL_TEXTURE_2D, NULL);
  glDisable(GL_TEXTURE_2D);

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);


  glColor3f(0.9f, 0.1f, 0.1f);

  //glDrawArrays(GL_LINE_STRIP, 0, 12);

  glDisable(GL_POLYGON_OFFSET_FILL);

  glDisableClientState(GL_VERTEX_ARRAY);


}

void Landscape::privateUpdate()
{
    float increment = speed_/this->fps_;
    distance += increment;
    matrix_ = glm::translate(matrix_, {0.0f, 0.0f, increment});
    if (distance >= length){
        distance -= length;
        matrix_ = glm::translate(matrix_, {0.0f, 0.0f, - length});
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

void Landscape::setSpeedZ(float speed){speed_ = speed;}

float Landscape::getHeightY(const ColSphereBody& target) const{
    auto zDist = distance - target.getWorldPos().z;

    // Put zDist in the correct domain, since the height is periodic
    while(zDist < 0.0f)
        zDist += length;
    while(zDist >= length)
        zDist -= length;

    float groundLevel;

    if(zDist <= length/3.0f){
        groundLevel = 0.0f;
    }else{
        groundLevel = rise_ * (1.0 - 3.0f*abs(zDist/length - 2.0f/3.0f));
    }

    return groundLevel + target.getRadius();
}
