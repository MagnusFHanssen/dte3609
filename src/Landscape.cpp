#include "../include/Landscape.hpp"
#include "../include/stb_image.h"
#include "../../glm-master/glm/gtc/matrix_transform.hpp"

#include <cmath>
#include <iostream>


Landscape::Landscape(std::shared_ptr<Shader> shader, float initialDistance, int repeats) :
    distance(initialDistance), shader_{shader}, repeats_{repeats}
{
    lightPos_= {0.0f, 0.0f, 0.0f};
}

Landscape::~Landscape()
{
}

void Landscape::privateInit()
{
    width = 40.0f;
    length = 60.0f;
    rise_ = 2.0f;

    texLoaded_ = false;
    normalsLoaded_ = false;

    int texScaleFactor = 5;

    auto const frac = length/3.0f;


  // Create vertex array
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

    // Texture number 1
    for (auto vec : vertexArray_){
        texCoordArray_.emplace_back(glm::vec2(vec.x/texScaleFactor, vec.z/texScaleFactor));
    }

    // Normals
    for (unsigned int i = 0; i < vertexArray_.size(); i += 4){
        glm::vec3 u = vertexArray_[i+2] - vertexArray_[i+1];
        glm::vec3 v = vertexArray_[i] - vertexArray_[i+1];
        glm::vec3 normal = glm::cross(u, v);
        normal = glm::normalize(normal);

        for (int j = 0; j < 4; j++){
            normalArray_.push_back(normal);
        }

    }

    // Bit of a hack to stuff all of the above into a single vector
    for (unsigned int i = 0; i < vertexArray_.size(); i++){
        MyVertex vert;
        vert.Position = vertexArray_[i];
        vert.Normal = normalArray_[i];
        vert.TexCoord = texCoordArray_[i];

        // Temporary. I hope...
        vert.TexCoord2 = texCoordArray_[i];

        combinedArray_.push_back(vert);
    }

    initBuffers();

    texLoaded_ = loadTexture("rock2.jpg", texName_);

    if (!texLoaded_){
        std::cout << "Could not load texture rock2.jpg" << std::endl;
    }

    normalsLoaded_ = loadTexture("rock2normal.jpg", normalMap_);

    if (!normalsLoaded_){
        std::cout << "Could not load texture rock2normals.jpg" << std::endl;
    }

    matrix_ = glm::translate(matrix_, {0.0f, 0.0f, distance});
}

void Landscape::privateRender()
{
  /* Old stuff
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

  glDisableClientState(GL_VERTEX_ARRAY);*/
    //std::cout << glGetError() << std::endl;

    shader_->enable();

    //std::cout << glGetError() << std::endl;
    // Light
    shader_->setVec3("lightPos", lightPos_);

    // Matrices
    shader_->setMat4("model", matrix_);
    shader_->setMat4("view", viewMatrix_);
    shader_->setMat4("projection", projectionMatrix_);

    //std::cout << glGetError() << std::endl;

    // Bind textures:
    //assignUniformInt("Texture1", 0, shader_);
    shader_->setInt("Texture1", 0);
    //std::cout << "163: " << glGetError() << std::endl;
    glActiveTexture(GL_TEXTURE0);
    //std::cout << "165: " << glGetError() << std::endl;
    glBindTexture(GL_TEXTURE_2D, texName_);
    //std::cout << "167: " << glGetError() << std::endl;

    //assignUniformInt("Texture2", 1, shader_);
    shader_->setInt("Texture2", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalMap_);

    //std::cout << glGetError() << std::endl;

    // Draw array
    glBindVertexArray(VAO_);
    glDrawArrays(GL_QUADS, 0, vertexArray_.size());

    glm::mat4 temp = glm::translate(matrix_, {0.0f, 0.0f, length});
    //assignUniformM4("model", temp, shader_);
    shader_->setMat4("model", temp);
    glDrawArrays(GL_QUADS, 0, vertexArray_.size());

    temp = glm::translate(matrix_, {0.0f, 0.0f, -length});
    //assignUniformM4("model", temp, shader_);
    shader_->setMat4("model", temp);
    glDrawArrays(GL_QUADS, 0, vertexArray_.size());

    temp = glm::translate(matrix_, {0.0f, 0.0f, -2*length});
    //assignUniformM4("model", temp, shader_);
    shader_->setMat4("model", temp);
    glDrawArrays(GL_QUADS, 0, vertexArray_.size());

    temp = glm::translate(matrix_, {0.0f, 0.0f, -3*length});
    //assignUniformM4("model", temp, shader_);
    shader_->setMat4("model", temp);
    glDrawArrays(GL_QUADS, 0, vertexArray_.size());

    glBindVertexArray(0);

    //std::cout << glGetError() << std::endl;

    shader_->disable();
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

bool Landscape::loadTexture(std::string name, GLuint &texName)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName);

    glBindTexture(GL_TEXTURE_2D, texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    std::string pathStr = "./resources/textures/";
    pathStr.append(name);

    const char *path = &pathStr[0];

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

    if(data)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else
        return false;

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, NULL);

    return true;
}

void Landscape::initBuffers(){
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);

    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, combinedArray_.size() * sizeof (MyVertex), &combinedArray_[0], GL_STATIC_DRAW);

    // Vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (void*)0);
    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (void*)offsetof(MyVertex, Normal));
    // Texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (void*)offsetof(MyVertex, TexCoord));

    // Normal map - Might not be properly implemented
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertex), (void*)offsetof(MyVertex, TexCoord2));

    glBindVertexArray(0);
}

void Landscape::setSpeedZ(float speed){speed_ = speed;}

float Landscape::getSpeedZ(){return speed_;}

void Landscape::incrementSpeedZ(float increment){
    speed_ += increment;
}
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


