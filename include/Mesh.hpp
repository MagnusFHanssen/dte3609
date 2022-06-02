#pragma once


#include "Shader.hpp"
#include "../../glm-master/glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <vector>
#include <string>

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
  glm::vec3 Tangent;
  glm::vec3 Bitangent;
};

struct Texture {
  unsigned int id;
  std::string type;
  std::string path;
};

class Mesh
{
public:
  Mesh(std::vector<Vertex>, std::vector<unsigned int> indices, std::vector<Texture> textures);

  // Mesh
  std::vector<Vertex> vertices_;
  std::vector<unsigned int> indices_;
  std::vector<Texture> textures_;

  // functions
  void draw(std::shared_ptr<Shader> shader);


private:
  GLuint VAO_;
  GLuint VBO_;
  GLuint EBO_;

  void setupMesh();


};

