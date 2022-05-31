#pragma once

#include <windows.h>
#include "SceneObject.hpp"
#include <vector>

class Camera : public SceneObject
{
	public:
		Camera();
		~Camera();

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void moveBackward();
    void moveForward();

    void turnUp();
    void turnDown();
    void turnLeft();
    void turnRight();
    
  protected:
    void privateInit();
		void privateRender();
		void privateUpdate();

	private:
        float speed;
  
};


