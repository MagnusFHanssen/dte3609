#pragma once

#include <windows.h>
#include "SceneObject.hpp"
#include "ColSphereBody.hpp"

class Character : public SceneObject, public ColSphereBody
{
	public:
        Character(float xPos = 0.0f, float yPos = 2.0f);
        ~Character();

        void moveLeft();
        void moveRight();

        void setYPos(float yPos);

        float getLife();
        float doDamage(float damage);
        void fullHeal();
        void setLife(float life);

        void setMaxLife(float life);
        float getMaxLife();

        glm::vec3 getWorldPos() const;
        float getRadius() const;


  protected:
    void privateInit();
		void privateRender();
		void privateUpdate();

	private:
        bool loadTextures();

	  float speed_;
      float maxLife_;
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

