#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"

class Character : public SceneObject
{
	public:
        Character();
        ~Character();

  protected:
    void privateInit();
		void privateRender();
		void privateUpdate();

	private:
	  float speed_;
    float life_;
    float armor_;
    
};

