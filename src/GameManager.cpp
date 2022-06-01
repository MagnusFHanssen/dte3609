#include "../include/GameManager.hpp"
#include <string.h>


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
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  sText_.reset(new SText());

  // Fog stuff
  //glEnable(GL_FOG);
  //GLfloat fogColor[] {0.9f, 0.9f, 0.9f, 1.0f};
  //glFogfv(GL_FOG_COLOR, fogColor);
  //glFogf(GL_FOG_DENSITY, 0.01f);
  //glFogi(GL_FOG_MODE, GL_EXP);

  finished_ = false;

  // Light
  sunPos = {20.0f, 100.0f, -30.0f};

  // Adding shaders
  addShader("Skybox");
  addShader("Landscape");
  addShader("Character");
  addShader("Rock");


  // Adding the camera to the scene
  cam_.reset(new Camera());

  // Objects post Shader
  skybox_.reset(new Skybox(getShaderPtr("Skybox")));
  this->addSubObject(skybox_);

  ls_.reset(new Landscape(getShaderPtr("Landscape"), 10.0f));
  this->addSubObject(ls_);
  ls_->setSpeedZ(0.0f);

  ls_->setLightPos(sunPos);

  character_.reset(new Character(getShaderPtr("Character")));
  this->addSubObject(character_);

  character_->setLightPos(sunPos);


  rockModel_.reset(new Model("./resources/models/Rock1.obj"));
  rockModel_->meshes.erase(rockModel_->meshes.begin());

  auto rockShader = getShaderPtr("Rock");
  rockShader->enable();
  rockShader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
  rockShader->setVec3("lightPos", sunPos);
  rockShader->disable();

  //std::shared_ptr<Rock> rock;
  //rock.reset(new Rock(getShaderPtr("Rock"), ls_, rockModel_, false));

  //this->addSubObject(rock);
  //rocks_.push_back(rock);

  for(int i = 0; i < 8; i++){
      rocks_.emplace_back(new Rock(getShaderPtr("Rock"), ls_, rockModel_, false));
      this->addSubObject(rocks_.back());
  }

  for(int i = 0; i < 4; i++){
      rocks_.emplace_back(new Rock(getShaderPtr("Rock"), ls_, rockModel_, true));
      this->addSubObject(rocks_.back());
      rocks_.back()->setDamage(2.0f);
  }

  rocksSpread_ = false;

  /*
  bboard_.reset(new Billboard(4.0f, 1.0f, glm::vec3(0.0f, 3.0f, 0.0f), character_, cam_));
  this->addSubObject(bboard_);

  particle_.reset(new Particle({0.0f, 40.0f, 0.0f}, {0.0f, -2.0f, 0.0f}));
  this->addSubObject(particle_);

  char life[20];
  snprintf(life, sizeof(life), "Life: %.1f / %.1f", character_->getLife(), character_->getMaxLife());
  text_.reset(new Text(std::string(life), {20.0f, 20.0f, 10.0f}, GLUT_STROKE_ROMAN, STROKE_CHAR, {1.0f, 0.0f, 0.0f}));
  this->addSubObject(text_);

  ls_->setSpeedZ(10.0f);

  mapList_.push_back(ls_);
  mapList_.push_back(character_);*/

  timer_ = 0.0f;
}

void GameManager::privateRender()
{
  // Nothing to render
    if(finished_){
        char outText[40];
        snprintf(outText, sizeof (outText), "You finished with a score of %.1f!", endTime_);
        sText_->RenderText(std::string(outText), 70.0f, 340.0f, 1.0f, glm::vec3(0.9, 0.3f, 0.1f));
        sText_->RenderText("Restart the game to play again!", 70.0f, 300.0f, 1.0f, glm::vec3(0.9, 0.3f, 0.1f));
    }
}

void GameManager::privateUpdate()
{
  // Instead of adding alle objects in the scene as subobject to the camera they are added as subobjects
  // to the game manager. Therefore, we set the game manager matrix equal to the camera matrix. 
  this->matrix_ = cam_->getMatrix();
  updateViewMatrix(cam_->getMatrix());
    //char life[20];
    //snprintf(life, sizeof(life), "Life: %.1f / %.1f", character_->getLife(), character_->getMaxLife());
    //text_->setString(std::string(life));

    if(!rocksSpread_){
        for (unsigned int i = 1; i < rocks_.size(); i++){
            rocks_.at(i)->setZ(Rock::MIN_Y - (i * 50.0f));
        }
        rocksSpread_ = true;
    }

    if(!finished_){
    character_->setYPos(ls_->getHeightY(*character_));

    timer_ += 1.0f/this->fps_;



    ls_->setSpeedZ(glm::max(0.0f, timer_ - 10.0f));

    // Collision logic:
    for (auto rock : rocks_){
        if(rock->active && character_->detectCollision(rock.get())){
            float damage = rock->collide();
            if(character_->doDamage(damage) <= 0.0f){
                finished_ = true;
                endTime_ = timer_;

                for (auto child : rocks_){
                    this->removeSubObject(child);
                }
                this->removeSubObject(character_);
                this->removeSubObject(ls_);
                this->removeSubObject(skybox_);
            }
        }
    }
    }
}

std::shared_ptr<Camera> GameManager::getCam()
{
  return cam_;
}
std::shared_ptr<Character> GameManager::getMC()
{
    return character_;
}

void GameManager::addShader(std::string name){
    auto shader = new Shader();

    std::string  path = "./resources/shaders/";
    path.append(name);

    char *p = &path[0];
    shader->initShaders(p);
    shaders_[name] = *shader;
}

std::shared_ptr<Shader> GameManager::getShaderPtr(std::string name){
    std::shared_ptr<Shader> ptr(nullptr);
    ptr = std::make_shared<Shader>(shaders_[name]);
    return ptr;
}

bool GameManager::isFinished(){return false;}
