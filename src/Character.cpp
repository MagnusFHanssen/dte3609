
#include "../include/Character.hpp"
#include <iostream>

#include "../include/stb_image.h"
#include "../../glm-master/glm/gtc/matrix_transform.hpp"

Character::Character( std::shared_ptr<Shader> shader, float xPos, float yPos) :
   _xPos(xPos), _yPos(yPos), shader_{shader}
{
    gravity = {0.0f, -9.81f, 0.0f};
    attached = false;

    /*charModel_ = Model("./resources/models/Rock1.obj");
    charModel_.meshes.erase(charModel_.meshes.begin());*/

    charModel_ = Model("./resources/models/car.obj");
}

Character::~Character()
{
}

void Character::privateInit()
{
    turnRate_ = 10.0f;
    _rotation = 0.0f;

    scale_ = 12.0f;

    maxLife_ = 10.0f;
    life_ = maxLife_;
    armor_ = 0.0f;
    xBound_ = 16.0f;

    active = true;

    shader_->enable();
    shader_->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shader_->setVec3("lightPos", lightPos_);
    shader_->disable();

    scaleRotMat_ = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleRotMat_ = glm::scale(scaleRotMat_, {scale_, scale_, scale_});
}

void Character::privateRender()
{
    shader_->enable();
    shader_->setMat4("projection", projectionMatrix_);
    shader_->setMat4("view", viewMatrix_);
    shader_->setMat4("model",  matrix_ * scaleRotMat_ );
    shader_->setFloat("health", life_/maxLife_);
    shader_->disable();

    charModel_.draw(shader_);
}

void Character::privateUpdate()
{

}

void Character::moveLeft()
{
    float increment = turnRate_/this->fps_;
    if(_xPos - increment >= -xBound_){
        _xPos -= increment;
        matrix_ = glm::translate(matrix_, {-increment, 0.0f, 0.0f});
    }

}

void Character::moveRight()
{
    float increment = turnRate_/this->fps_;
    if(_xPos + increment <= xBound_){
        _xPos += increment;
        matrix_ = glm::translate(matrix_, {increment, 0.0f, 0.0f});
    }

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
    return scale_/2.2f;
}
