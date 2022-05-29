#include "../include/Billboard.hpp"
#include "../../glm-master/glm/glm.hpp"
#include "../../glm-master/glm/gtc/matrix_transform.hpp"

Billboard::Billboard(){}

Billboard::Billboard(GLfloat width, GLfloat height, glm::vec3 startPos,
                     std::shared_ptr<SceneObject> obj, std::shared_ptr<Camera> cam):
    obj_{obj}, cam_{cam}, width_{width}, height_{height}, startPos_{startPos} {}

Billboard::~Billboard(){}


void Billboard::privateInit()
{
    matrix_ = glm::translate(matrix_, startPos_);

    drawList_ = glGenLists(1);
    glNewList(drawList_, GL_COMPILE);

    glBegin(GL_QUADS);

    glColor3f(0.5f, 0.0f, 1.0f);

    glVertex3f(-width_/2.0f, 0.0f, 0.0f);
    glVertex3f(width_/2.0f, 0.0f, 0.0f);
    glVertex3f(width_/2.0f, height_, 0.0f);
    glVertex3f(-width_/2.0f, height_, 0.0f);

    glEnd();

    glEndList();

}

void Billboard::privateRender(){
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glCallList(drawList_);
    glDisable(GL_COLOR_MATERIAL);
}

void Billboard::privateUpdate()
{
    auto const objMat = obj_->getMatrix();
    auto const camMat = cam_->getMatrix();

    glm::vec3 const boardPos {matrix_[3].x, matrix_[3].y, matrix_[3].z};

    // Get camera position
    glm::vec3 const camPos = - glm::vec3( camMat[3].x, camMat[3].y, camMat[3].z );
    glm::vec3 const camUp = {camMat[0][1], camMat[1][1], camMat[2][1]};
    glm::vec3 const camRight {camMat[0][0], camMat[1][0], camMat[2][0]};

    glm::vec3 const facing = glm::normalize(camPos - boardPos);

    matrix_[0] = glm::vec4(camRight, 0.0f);
    matrix_[1] = glm::vec4(camUp, 0.0f);
    matrix_[2] = glm::vec4(facing, 0.0f);

    matrix_[3][0] = objMat[3][0] + startPos_.x;
    matrix_[3][1] = objMat[3][1] + startPos_.y;
    matrix_[3][2] = objMat[3][2] + startPos_.z;


}
