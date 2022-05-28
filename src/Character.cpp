
#include "../include/Character.hpp"
#include <iostream>

Character::Character()
{

}

Character::~Character()
{
}

void Character::privateInit()
{

}

void Character::privateRender()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    float size = 50.0f;
    float sizez = -100.0f;
    glBegin(GL_QUADS);
      // Near Face
      glNormal3f( 0.0f, 0.0f, 1.0f);
      glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size,  sizez);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size,  sizez);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size,  sizez);
      glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size,  sizez);
    glEnd();
}

void Character::privateUpdate()
{

}

