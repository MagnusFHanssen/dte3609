#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "SceneObject.hpp"
#include "Landscape.hpp"
#include "Character.hpp"
#include "Camera.hpp"
#include "Billboard.hpp"
#include "Particle.hpp"
#include "Text.hpp"

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
    std::shared_ptr<Landscape> ls_;
    std::shared_ptr<Character> character_;
    std::shared_ptr<Camera> cam_;
    std::shared_ptr<Billboard> bboard_;
    std::shared_ptr<Particle> particle_;
    std::shared_ptr<Text> text_;

    std::vector<std::shared_ptr<SceneObject>> mapList_;

};

