#include "../include/Rock.hpp"
#include <iostream>


#include "../include/stb_image.h"
#include "../../glm-master/glm/gtc/matrix_transform.hpp"

// Constants
const float Rock::MIN_X = -18.0f;
const float Rock::MAX_X = 18.0f;
const float Rock::MIN_Y = 10.0f;
const float Rock::MAX_Y = 100.0f;
const float Rock::MIN_Z = -10.0f;
const float Rock::MAX_Z = 200.0f;

float randMToN(float M, float N)
{
    return M + (rand() / ( RAND_MAX / (N-M) ) );
}

Rock::Rock(std::shared_ptr<Shader> shader, std::shared_ptr<Landscape> ls, std::shared_ptr<Model> model, bool falling):
    shader_{shader}, ls_{ls}, model_{model}, falling_{falling}
{
    gravity = {0.0f, -9.81f, 0.0f};
    attached = false;
    worldPos = {0.0f, 0.0f, 0.0f};
}

Rock::~Rock(){}

void Rock::privateInit(){
    respawn();

    shader_->enable();
    shader_->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shader_->setVec3("lightPos", lightPos_);
    shader_->disable();
}

void Rock::privateRender(){
    if(active){
    shader_->enable();
    shader_->setMat4("projection", projectionMatrix_);
    shader_->setMat4("view", viewMatrix_);
    shader_->setMat4("model",  matrix_ * scaleRotMat_ );
    shader_->disable();

    model_->draw(shader_);
    }
}

void Rock::privateUpdate(){
    glm::vec3 mov = {0.0f, 0.0f, ls_->getSpeedZ()/this->fps_};
    if(!attached){
        mov += gravity/float(this->fps_);
        attached = ls_->detectCollision(*this);
    }
    worldPos += mov;
    matrix_ = glm::translate(matrix_, mov);

    if (worldPos.z > MAX_Z){
        respawn();
    }
}

void Rock::respawn(){
    active_ = true;
    float y;
    if(falling_){
        y = randMToN(MIN_Y, MAX_Y);
        attached = false;
    }else{
        attached = true;
        y = ls_->getHeightY(*this);
    }
    float x = randMToN(MIN_X, MAX_X);
    float z = MIN_Z;

    scale_ = randMToN(2.0f, 3.0f);
    setPos(x, y, z);


    scaleRotMat_ = glm::scale(glm::mat4(1.0f), {scale_, scale_, scale_});

}

void Rock::setPos(float x, float y, float z){
    glm::vec3 diff {x - worldPos.x, y - worldPos.y, z - worldPos.z};
    worldPos = {x, y, z};
    matrix_ = glm::translate(matrix_, diff);
}
void Rock::setDamage(float damage){damage_ = damage;}

float Rock::collide(){
    active_ = false;
    return damage_;
}

glm::vec3 Rock::getWorldPos() const{
    return worldPos;
}

float Rock::getRadius() const{
    return scale_;
}
