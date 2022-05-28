#include "../include/Landscape.hpp"

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

    auto const frac = length/3.0f;



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
}

void Landscape::privateRender()
{
  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0.0f, 0.0f, distance);


  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  glColor3f(0.45f, 0.90f, 0.0f);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertexArray_.front().x);

  glEnable(GL_AUTO_NORMAL);
  glDrawArrays(GL_QUADS, 0, 12);
  glDisable(GL_AUTO_NORMAL);

  glDisableClientState(GL_VERTEX_ARRAY);

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

