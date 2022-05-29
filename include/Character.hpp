#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"

class Character : public SceneObject
{
	public:
        Character(float xPos = 0.0f, float yPos = 2.0f);
        ~Character();

        void moveLeft();
        void moveRight();

  protected:
    void privateInit();
		void privateRender();
		void privateUpdate();

	private:
        bool loadTextures();

	  float speed_;
    float life_;
    float armor_;

    float turnRate_;

    float _xPos;
    float _yPos;

    float _rotation;

    float scale_;

    GLuint dList_;
    GLuint dNormal_;

    GLuint texName_;

    bool texLoaded_;


    
};

