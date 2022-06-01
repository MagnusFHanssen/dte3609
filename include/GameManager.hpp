#pragma once

#include <windows.h>
#include <unordered_map>
#include "SceneObject.hpp"

#include "Landscape.hpp"
#include "Character.hpp"
#include "Camera.hpp"
#include "Billboard.hpp"
#include "Particle.hpp"
#include "Text.hpp"
#include "Skybox.hpp"
#include "Rock.hpp"

class GameManager : public SceneObject
{
	public:
		GameManager();
		~GameManager();
    
    std::shared_ptr<Camera> getCam();
    std::shared_ptr<Character> getMC();

  protected:
    virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();

	private:
    void addShader(std::string name);
    std::shared_ptr<Shader> getShaderPtr(std::string name);

    glm::vec3 sunPos;

    std::shared_ptr<Landscape> ls_;
    std::shared_ptr<Character> character_;
    std::shared_ptr<Camera> cam_;
    std::shared_ptr<Billboard> bboard_;
    std::shared_ptr<Particle> particle_;
    std::shared_ptr<Text> text_;
    std::shared_ptr<Skybox> skybox_;

    std::vector<std::shared_ptr<Rock>> rocks_;

    std::vector<std::shared_ptr<SceneObject>> mapList_;

    std::unordered_map<std::string, Shader> shaders_;

    std::shared_ptr<Model> rockModel_;

};

