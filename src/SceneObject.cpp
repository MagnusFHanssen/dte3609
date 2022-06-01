#include "../include/SceneObject.hpp"

#include <windows.h>
#include "../../glm-master/glm/glm.hpp"
#include "../../glm-master/glm/gtc/type_ptr.hpp"

// NB! Check matrix mult and scoped_ptr

SceneObject::SceneObject()
{
  matrix_ = glm::mat4(1.0f);
}

SceneObject::~SceneObject()
{
}

void SceneObject::render()
{
  glPushMatrix();
    glMultMatrixf(glm::value_ptr(matrix_));
    this->privateRender();
    for(std::vector<std::shared_ptr<SceneObject> >::iterator it = children_.begin();
        it != children_.end(); it++)
        (*it)->render();
  glPopMatrix();
}

void SceneObject::update(double fps)
{
  this->fps_ = fps;
  this->privateUpdate();
  for(std::vector<std::shared_ptr<SceneObject> >::iterator it = children_.begin();
      it != children_.end(); it++)
      (*it)->update(fps);
}

void SceneObject::init()
{
  this->privateInit();
  for(std::vector<std::shared_ptr<SceneObject> >::iterator it = children_.begin();
      it != children_.end(); it++)
      (*it)->init();
}

void SceneObject::addSubObject(std::shared_ptr<SceneObject> newchild)
{
  children_.push_back(newchild);
}

void SceneObject::removeSubObject(const std::shared_ptr<SceneObject> child)
{
  for(std::vector<std::shared_ptr<SceneObject> >::iterator it = children_.begin();
      it != children_.end(); it++)
    if(*it == child)
    {
      children_.erase(it);
      break;
    }
}

// Custom methods

void SceneObject::updateViewMatrix(glm::mat4 newMatrix){
    viewMatrix_ = newMatrix;
    for(auto child : children_){
        child->viewMatrix_ = newMatrix;
    }
}

void SceneObject::updateProjectionMatrix(glm::mat4 newMatrix){
    projectionMatrix_ = newMatrix;
    for(auto child : children_){
        child->projectionMatrix_ = newMatrix;
    }
}

void SceneObject::setLightPos(glm::vec3 lightPos){
    lightPos_ = lightPos;
}

