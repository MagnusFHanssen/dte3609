
#include "../include/Character.hpp"
#include <iostream>

#include "../include/stb_image.h"
#include "../../glm-master/glm/gtc/matrix_transform.hpp"

Character::Character( std::shared_ptr<Shader> shader, float xPos, float yPos) :
   _xPos(xPos), _yPos(yPos), shader_{shader}
{
    gravity = {0.0f, -9.81f, 0.0f};
    attached = false;

    charModel_ = Model("./resources/models/Car.obj");
}

Character::~Character()
{
}

void Character::privateInit()
{
    turnRate_ = 10.0f;
    _rotation = 0.0f;

    scale_ = 2.0f;

    maxLife_ = 10.0f;
    life_ = maxLife_;
    armor_ = 0.0f;


    /*GLfloat const verts[8][3] = {{scale_, -scale_, scale_},
                           {scale_, scale_, scale_},
                           {scale_, -scale_, -scale_},
                           {scale_, scale_, -scale_},
                           {-scale_, -scale_, scale_},
                           {-scale_, scale_, scale_},
                           {-scale_, -scale_, -scale_},
                           {-scale_, scale_, -scale_}};
    GLfloat const norms[6][3] = {{1.0f, 0.0f, 0.0f}, // X+
                                 {0.0f, 1.0f, 0.0f}, // Y+
                                 {0.0f, 0.0f, 1.0f}, // Z+
                                 {-1.0f, 0.0f, 0.0f}, // X-
                                 {0.0f, -1.0f, 0.0f}, // Y-
                                 {0.0f, 0.0f, -1.0f}}; // Z-

    GLfloat const tex[6][2] = {{0.0f, 0.0f},
                               {1.0f, 0.0f},
                               {0.0f, 0.5f},
                               {1.0f, 0.5f},
                               {0.0f, 1.0f},
                               {1.0f, 1.0f}};

    GLfloat normsSoft[8][3];

    float nMag = std::sqrt(3 * std::pow(scale_, 2));
    for (int i = 0; i < 8; i++){
       for (int j = 0; j < 3; j++){
           normsSoft[i][j] = verts[i][j] / nMag;
       }
    }

    std::vector<int> indexes {0, 2, 1, 3, 1, 2,
                             1, 3, 5, 7, 5, 3,
                             5, 7, 4, 6, 4, 7,
                             4, 6, 0, 2, 0, 6,
                             1, 5, 0, 4, 0, 5,
                             6, 7, 2, 3, 2, 7};

    auto const drawCharacter = [&verts, &norms, &tex, &normsSoft, &indexes]{
        glBegin(GL_TRIANGLES);

        glNormal3fv(norms[0]); glTexCoord2fv(tex[0]); glVertex3fv(verts[0]); // X+ side
        glNormal3fv(norms[0]); glTexCoord2fv(tex[2]); glVertex3fv(verts[2]);
        glNormal3fv(norms[0]); glTexCoord2fv(tex[1]); glVertex3fv(verts[1]);
        glNormal3fv(norms[0]); glTexCoord2fv(tex[3]); glVertex3fv(verts[3]);
        glNormal3fv(norms[0]); glTexCoord2fv(tex[1]); glVertex3fv(verts[1]);
        glNormal3fv(norms[0]); glTexCoord2fv(tex[2]); glVertex3fv(verts[2]);

        glNormal3fv(norms[1]); glTexCoord2fv(tex[2]); glVertex3fv(verts[1]); // Y+ side
        glNormal3fv(norms[1]); glTexCoord2fv(tex[4]); glVertex3fv(verts[3]);
        glNormal3fv(norms[1]); glTexCoord2fv(tex[3]); glVertex3fv(verts[5]);
        glNormal3fv(norms[1]); glTexCoord2fv(tex[5]); glVertex3fv(verts[7]);
        glNormal3fv(norms[1]); glTexCoord2fv(tex[3]); glVertex3fv(verts[5]);
        glNormal3fv(norms[1]); glTexCoord2fv(tex[4]); glVertex3fv(verts[3]);

        glNormal3fv(norms[3]); glTexCoord2fv(tex[0]); glVertex3fv(verts[5]); // X- side
        glNormal3fv(norms[3]); glTexCoord2fv(tex[2]); glVertex3fv(verts[7]);
        glNormal3fv(norms[3]); glTexCoord2fv(tex[1]); glVertex3fv(verts[4]);
        glNormal3fv(norms[3]); glTexCoord2fv(tex[3]); glVertex3fv(verts[6]);
        glNormal3fv(norms[3]); glTexCoord2fv(tex[1]); glVertex3fv(verts[4]);
        glNormal3fv(norms[3]); glTexCoord2fv(tex[2]); glVertex3fv(verts[7]);

        glNormal3fv(norms[4]); glTexCoord2fv(tex[2]); glVertex3fv(verts[4]); // Y- side
        glNormal3fv(norms[4]); glTexCoord2fv(tex[4]); glVertex3fv(verts[6]);
        glNormal3fv(norms[4]); glTexCoord2fv(tex[3]); glVertex3fv(verts[0]);
        glNormal3fv(norms[4]); glTexCoord2fv(tex[5]); glVertex3fv(verts[2]);
        glNormal3fv(norms[4]); glTexCoord2fv(tex[3]); glVertex3fv(verts[0]);
        glNormal3fv(norms[4]); glTexCoord2fv(tex[4]); glVertex3fv(verts[6]);

        glNormal3fv(norms[2]); glTexCoord2fv(tex[0]); glVertex3fv(verts[1]); // Z+ side
        glNormal3fv(norms[2]); glTexCoord2fv(tex[2]); glVertex3fv(verts[5]);
        glNormal3fv(norms[2]); glTexCoord2fv(tex[1]); glVertex3fv(verts[0]);
        glNormal3fv(norms[2]); glTexCoord2fv(tex[3]); glVertex3fv(verts[4]);
        glNormal3fv(norms[2]); glTexCoord2fv(tex[1]); glVertex3fv(verts[0]);
        glNormal3fv(norms[2]); glTexCoord2fv(tex[2]); glVertex3fv(verts[5]);

        glNormal3fv(norms[5]); glTexCoord2fv(tex[0]); glVertex3fv(verts[6]); // Z- side
        glNormal3fv(norms[5]); glTexCoord2fv(tex[2]); glVertex3fv(verts[7]);
        glNormal3fv(norms[5]); glTexCoord2fv(tex[1]); glVertex3fv(verts[2]);
        glNormal3fv(norms[5]); glTexCoord2fv(tex[3]); glVertex3fv(verts[3]);
        glNormal3fv(norms[5]); glTexCoord2fv(tex[1]); glVertex3fv(verts[2]);
        glNormal3fv(norms[5]); glTexCoord2fv(tex[2]); glVertex3fv(verts[7]);

        //for (int i : indexes){
        //        glNormal3fv(normsSoft[i]); glVertex3fv(verts[i]);
        //    }

        glEnd();
    };

    dList_ = glGenLists(1);
    glNewList(dList_, GL_COMPILE);
    drawCharacter();
    glEndList();*/

    /*auto const drawNormals = [&verts, &normsSoft, &indexes]{
        glBegin(GL_LINES);

        for (int i : indexes){
            glVertex3fv(verts[i]);
            glVertex3f(verts[i][0] + normsSoft[i][0],
                    verts[i][1] + normsSoft[i][1],
                    verts[i][2] + normsSoft[i][2]);
        }

        glEnd();

    };

    dNormal_ = glGenLists(1);
    glNewList(dNormal_, GL_COMPILE);
    drawNormals();
    glEndList();*/

    /*texLoaded_ = loadTextures();

    // Translation:
    matrix_ = glm::translate(matrix_, {_xPos, _yPos, 0.0f});
    matrix_ = glm::rotate(matrix_, _rotation, {0.0f, 1.0f, 0.0f});*/


}

void Character::privateRender()
{
    /*glColor3f(1.0f, 0.0f, 0.0f);
    float size = 50.0f;
    float sizez = -100.0f;
    glBegin(GL_QUADS);
      // Near Face
      glNormal3f( 0.0f, 0.0f, 1.0f);
      glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size,  sizez);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size,  sizez);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size,  sizez);
      glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size,  sizez);
    glEnd();*/

    /*glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //glMatrixMode(GL_MODELVIEW);
    //glTranslatef(_xPos, _yPos, 0.0f);
    //glRotatef(_rotation, 0.0f, 1.0f, 0.0f);

    if (texLoaded_){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texName_);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(1.0f, 1.0f, 1.0f);

        glCallList(dList_);

        glDisable(GL_COLOR_MATERIAL);
        glBindTexture(GL_TEXTURE_2D, NULL);
        glDisable(GL_TEXTURE_2D);

    }else{
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glColor3f(0.9f, 0.1f, 0.1f);

    //glColorMaterial(GL_FRONT, GL_SPECULAR);
    //glColor3f(0.94f, 0.18f, 0.18f);

    glCallList(dList_);

    glDisable(GL_COLOR_MATERIAL);
    }
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    //glColor3f(0.1f, 0.1f, 0.9f);
    //glCallList(dNormal_);*/
}

void Character::privateUpdate()
{

}

void Character::moveLeft()
{
    float increment = turnRate_/this->fps_;
    _xPos -= increment;
    matrix_ = glm::translate(matrix_, {-increment, 0.0f, 0.0f});

    //_rotation += turnRate_;
}

void Character::moveRight()
{
    float increment = turnRate_/this->fps_;
    _xPos += increment;
    matrix_ = glm::translate(matrix_, {increment, 0.0f, 0.0f});

    //_rotation -= turnRate_;
}

void Character::setYPos(float yPos){
    auto diff = yPos - _yPos;
    matrix_ = glm::translate(matrix_, {0.0f, diff, 0.0f});
    _yPos = yPos;
}

float Character::getLife(){return life_;}

float Character::doDamage(float damage){
    life_ -= (damage - armor_);
    return life_;
}

void Character::setLife(float life){life_ = life;}

void Character::fullHeal(){life_ = maxLife_;}

void Character::setMaxLife(float life){maxLife_ = life;}

float Character::getMaxLife(){return maxLife_;}

bool Character::loadTextures()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName_);

    glBindTexture(GL_TEXTURE_2D, texName_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("./resources/textures/block.jpg", &width, &height, &nrChannels, 0);

    if(data)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else
        return false;

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, NULL);

    return true;
}

glm::vec3 Character::getWorldPos() const{
    return {_xPos, _yPos, 0.0f};
}

float Character::getRadius() const{
    return scale_;
}
