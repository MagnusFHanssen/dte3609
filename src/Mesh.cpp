#include "../include/Mesh.hpp"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
  this->vertices_ = vertices;
  this->indices_ = indices;
  this->textures_ = textures;

  setupMesh();
}

void Mesh::draw(std::shared_ptr<Shader> shader)
{
  // bind appropriate textures
  unsigned int diffuseNr  = 1;
  unsigned int specularNr = 1;
  unsigned int normalNr   = 1;
  unsigned int heightNr   = 1;

  for(unsigned int i = 0; i < textures_.size(); i++)
  {
      glActiveTexture(GL_TEXTURE0 + i);
      std::string number;
      std::string name = textures_[i].type;
      if(name == "texture_diffuse")
          number = std::to_string(diffuseNr++);
      else if(name == "texture_specular")
          number = std::to_string(specularNr++);
      else if(name == "texture_normal")
          number = std::to_string(normalNr++);
       else if(name == "texture_height")
          number = std::to_string(heightNr++);

      glUniform1i(glGetUniformLocation(shader->getProg(), (name + number).c_str()), i);
      glBindTexture(GL_TEXTURE_2D, textures_[i].id);
  }
  shader->enable();
  // draw mesh
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);

  shader->disable();
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glActiveTexture(GL_TEXTURE0);

}


void Mesh::setupMesh()
{
  // create buffers/arrays
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ebo_);

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), &vertices_[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);

  // vertex Positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  // vertex normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
  // vertex texture coords
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
  // vertex tangent
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
  // vertex bitangent
  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

  glBindVertexArray(0);
}
