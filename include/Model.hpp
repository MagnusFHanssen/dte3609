#pragma once

#include <windows.h>
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "Mesh.hpp"


class Model
{
public:
  Model();
  Model(std::string const& path, bool gamma = false);

  // model data
  std::vector<Texture> textures_loaded;
  std::vector<Mesh> meshes;
  std::string directory;
  bool gammaCorrection;

  void draw(std::shared_ptr<Shader> shader);

private:
  void loadModel(std::string const& path);

  void processNode(aiNode *node, const aiScene *scene);

  Mesh processMesh(aiMesh* mesh, const aiScene *scene);

  std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

  unsigned int textureFromFile(const char* path, const std::string &directory, bool gamma = false);
};

