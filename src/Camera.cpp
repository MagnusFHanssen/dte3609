#include "../include/Camera.hpp"
#include "../../glm-master/glm/glm.hpp"
#include "../../glm-master/glm/gtc/matrix_transform.hpp"

#include <iostream>

#define PIOVER180 0.0174532925199

Camera::Camera()
{
  matrix_ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -50.0f));
}

Camera::~Camera()
{
}

void Camera::privateInit()
{

}


void Camera::privateRender()
{
  // not drawing any camera geometry
}

void Camera::privateUpdate()
{

}

void Camera::moveRight()
{
  matrix_ = glm::translate(matrix_, glm::vec3(-5.0f, 0.0f, 0.0f));
}
void Camera::moveLeft()
{
  matrix_ = glm::translate(matrix_, glm::vec3(5.0f, 0.0f, 0.0f));
}
void Camera::moveUp()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, -5.0f, 0.0f));
}
void Camera::moveDown()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 5.0f, 0.0f));
}
void Camera::moveForward()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 5.0f));
}
void Camera::moveBackward()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -5.0f));
}

