#include "../include/GameManager.hpp"
#include <string.h>
//#include <format>

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::privateInit()
{
  // Set default OpenGL states
  glEnable(GL_CULL_FACE);
  glEnable(GL_LINEAR_MIPMAP_LINEAR);

  // Fog stuff
  glEnable(GL_FOG);

  GLfloat fogColor[] {0.9f, 0.9f, 0.9f, 1.0f};
  glFogfv(GL_FOG_COLOR, fogColor);
  glFogf(GL_FOG_DENSITY, 0.01f);
  glFogi(GL_FOG_MODE, GL_EXP);

  // Insert light for old GL
  GLfloat light_dir[] = {0.2f, 1.0f, -0.3f, 0.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_dir);

  GLfloat ambient[] = {0.4f, 0.4f, 0.4f};

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

  // Adding the camera to the scene
  cam_.reset(new Camera());

  ls_.reset(new Landscape(10.0f));
  this->addSubObject(ls_);

  character_.reset(new Character());
  this->addSubObject(character_);

  bboard_.reset(new Billboard(4.0f, 1.0f, glm::vec3(0.0f, 3.0f, 0.0f), character_, cam_));
  this->addSubObject(bboard_);

  particle_.reset(new Particle({0.0f, 40.0f, 0.0f}, {0.0f, -2.0f, 0.0f}));
  this->addSubObject(particle_);

  char life[20];
  snprintf(life, sizeof(life), "Life: %.1f / %.1f", character_->getLife(), character_->getMaxLife());
  text_.reset(new Text(std::string(life), {20.0f, 20.0f, 10.0f}, GLUT_STROKE_ROMAN, STROKE_CHAR, {1.0f, 0.0f, 0.0f}));
  this->addSubObject(text_);


}

void GameManager::privateRender()
{
  // Nothing to render
}

void GameManager::privateUpdate()
{
  // Instead of adding alle objects in the scene as subobject to the camera they are added as subobjects
  // to the game manager. Therefore, we set the game manager matrix equal to the camera matrix. 
  this->matrix_ = cam_->getMatrix();
    char life[20];
    snprintf(life, sizeof(life), "Life: %.1f / %.1f", character_->getLife(), character_->getMaxLife());
    text_->setString(std::string(life));
}

std::shared_ptr<Camera> GameManager::getCam()
{
  return cam_;
}
std::shared_ptr<Character> GameManager::getMC()
{
    return character_;
}
